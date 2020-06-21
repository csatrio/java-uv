#include "basic-libuv.c"
#include "jnihelper.h"
#include <stdlib.h>
#include <stdio.h>

#define FREE = 1;
#define OCCUPIED = 0;
typedef struct
{
    jobject callback;
    jobject bytebuffer;
    void *buffer_address;
    short is_free;
} attachment_t;

//method_pointer new_callback = NULL;
jobject callback_factory = NULL;
jclass bytebuffer_class = NULL;
jclass on_read_java = NULL;
jfieldID wrapper_address_field = NULL;
jfieldID bytebuffer_position_field = NULL;
jmethodID new_callback_method_id = NULL;
jmethodID on_read_java_method_id = NULL;
size_t SUGGESTED_SIZE = 65536;

static void init() {}

static inline void delete_ref(JNIEnv *_env, jobject jref)
{
    if (jref == NULL)
        return;
    _env->DeleteGlobalRef(jref);
    _env->DeleteLocalRef(jref);
    //_env->DeleteWeakGlobalRef(jref);
}

static void on_connect(connection c, int status)
{
    JNIEnv *_env = env();
    jobject callback = _env->CallObjectMethod(callback_factory, new_callback_method_id);
    jlong ptr = (jlong)c;
    _env->SetLongField(callback, wrapper_address_field, ptr);
    attachment_t *attachment = (attachment_t *)malloc(sizeof(attachment_t));
    memset(attachment, 0, sizeof(attachment_t));
    attachment->callback = callback;
    c->attachment = attachment;
}

static void on_read(connection c, ssize_t nread, const uv_buf_t *buf)
{
    JNIEnv *_env = env();
    attachment_t *attachment = (attachment_t *)c->attachment;
    jint pos = (jint)nread;
    _env->SetIntField(attachment->bytebuffer, bytebuffer_position_field, pos);
    _env->CallObjectMethod(attachment->callback, on_read_java_method_id, attachment->bytebuffer);
}

static void after_write(connection c, int status)
{
    print_error(status);
}

static void cleanup_attachment(void *attachment)
{
    if (attachment != NULL)
    {
        attachment_t *a = (attachment_t *)attachment;
        if (a->bytebuffer != NULL && a->is_free == JNI_FALSE)
        {
            JNIEnv *_env = env();
            a->is_free = JNI_TRUE;
            delete_ref(_env, a->bytebuffer);
            delete_ref(_env, a->callback);
            free(_env->GetDirectBufferAddress(a->bytebuffer));
        }
        a->bytebuffer = NULL;
        free(a);
    }
}

static void on_allocate(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    connection c = (connection)handle->data;
    attachment_t *attachment = (attachment_t *)c->attachment;

    // Allocation of read buffer happen only once per connection lifetime
    // Performance is high, because data is directly written into DirectByteBuffer by libuv.
    // This allows us to achive zero copy with single buffer (no buffer list to be maintained, etc).
    if (attachment->bytebuffer == NULL)
    {
        buf->base = (char *)malloc(suggested_size);
        buf->len = suggested_size;
        attachment->buffer_address = buf->base;
        attachment->bytebuffer = env()->NewDirectByteBuffer(buf->base, suggested_size);
        attachment->is_free = JNI_FALSE;
        fprintf(stderr, "on_allocate new [%p], suggested_size:%ld\n", buf, suggested_size);
    }
    else
    {
        buf->base = (char *)attachment->buffer_address;
        buf->len = suggested_size;
        //fprintf(stderr, "on_allocate [%p], suggested_size:%ld\n", buf, suggested_size);
    }
}

static void on_error(const char *error_name, const char *error_message, const char *at)
{
    fprintf(stderr, "%s: %s -- at:%s\n", error_name, error_message, at);
}

JNIEXPORT void JNICALL Java_com_csatrio_libuv_UvBridge_runServer(JNIEnv *_env, jobject uv_bridge, jstring ip, jint port, jobject _callback_factory, jclass callback_class)
{
    init_jvm(_env);
    callback_factory = _callback_factory;
    bytebuffer_class = _env->FindClass("java/nio/ByteBuffer");
    bytebuffer_position_field = _env->GetFieldID(bytebuffer_class, "position", "I");
    on_read_java = callback_class;
    on_read_java_method_id = _env->GetMethodID(on_read_java, "onRead", "(Ljava/nio/ByteBuffer;)V");
    wrapper_address_field = _env->GetFieldID(on_read_java, "wrapperAddress", "J");
    jclass new_callback_class = _env->GetObjectClass(callback_factory);
    new_callback_method_id = _env->GetMethodID(new_callback_class, "newCallback", "()Lcom/csatrio/libuv/CallbackHandle;");
    const char *binding_address = _env->GetStringUTFChars(ip, JNI_FALSE);
    fprintf(stderr, "libtcpnative server started at %s:%d\n", binding_address, port);
    run_server(binding_address, port, init, on_connect, on_read, after_write, cleanup_attachment, on_error, on_allocate);
    _env->ReleaseStringUTFChars(ip, binding_address);
}

JNIEXPORT void JNICALL Java_com_csatrio_libuv_UvBridge_write(JNIEnv *_env, jobject uv_bridge, jobject bytebuffer, jobject callback)
{
    jlong wrapper_address = _env->GetLongField(callback, wrapper_address_field);
    connection c = (connection)wrapper_address;
    attachment_t *attachment = (attachment_t *)c->attachment;
    jint position = _env->GetIntField(attachment->bytebuffer, bytebuffer_position_field);
    size_t pos = (size_t)position;
    write(c, (char *)attachment->buffer_address, pos);
}

JNIEXPORT void JNICALL Java_com_csatrio_libuv_UvBridge_disconnect(JNIEnv *_env, jobject uv_bridge, jobject callback)
{
    jlong wrapper_address = _env->GetLongField(callback, wrapper_address_field);
    connection c = (connection)wrapper_address;
    disconnect(c);
}