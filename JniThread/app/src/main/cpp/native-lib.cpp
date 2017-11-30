#include <jni.h>

#include "AndroidLog.h"
#include "pthread.h"

pthread_t pthread;//线程对象

void *threadDoThings(void *data)
{
    LOGD("jni thread do things");
    pthread_exit(&pthread);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ywl532_jnithread_JniThread_normalThread(JNIEnv *env, jobject instance) {
    // TODO
    LOGD("normal thread");
    //创建线程
    pthread_create(&pthread, NULL, threadDoThings, NULL);

}

