#include "libtcpnativejni.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

JavaVM *jvm = (JavaVM *)malloc(sizeof(long));
inline JNIEnv *env()
{
    JNIEnv *_env;
    jint rs = jvm->AttachCurrentThread((void **)&_env, NULL);
    assert(rs == JNI_OK);
    return _env;
}

void init_jvm(JNIEnv *_env){
    _env->GetJavaVM(&jvm);
}

/*
jbyteArray as_byte_array(JNIEnv *env, unsigned char* buf, int len) {
    jbyteArray array = env->NewByteArray (len);
    env->SetByteArrayRegion (array, 0, len, reinterpret_cast<jbyte*>(buf));
    return array;
}

unsigned char* as_unsigned_char_array(JNIEnv *env, jbyteArray array) {
    int len = env->GetArrayLength (array);
    unsigned char* buf = new unsigned char[len];
    env->GetByteArrayRegion (array, 0, len, reinterpret_cast<jbyte*>(buf));
    return buf;
}
*/