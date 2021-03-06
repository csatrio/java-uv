/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_csatrio_libuv_UvBridge */

#ifndef _Included_com_csatrio_libuv_UvBridge
#define _Included_com_csatrio_libuv_UvBridge
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_csatrio_libuv_UvBridge
 * Method:    runServer
 * Signature: (Ljava/lang/String;ILcom/csatrio/libuv/CallbackFactory;Ljava/lang/Class;)V
 */
JNIEXPORT void JNICALL Java_com_csatrio_libuv_UvBridge_runServer
  (JNIEnv *, jobject, jstring, jint, jobject, jclass);

/*
 * Class:     com_csatrio_libuv_UvBridge
 * Method:    write
 * Signature: (Ljava/nio/ByteBuffer;Lcom/csatrio/libuv/CallbackHandle;)V
 */
JNIEXPORT void JNICALL Java_com_csatrio_libuv_UvBridge_write
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     com_csatrio_libuv_UvBridge
 * Method:    disconnect
 * Signature: (Lcom/csatrio/libuv/CallbackHandle;)V
 */
JNIEXPORT void JNICALL Java_com_csatrio_libuv_UvBridge_disconnect
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
