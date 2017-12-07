//
// Created by ywl5320
//

#include "WlListener.h"
#include "WlAndroidLog.h"

WlListener::WlListener(JavaVM *vm, _JNIEnv *env, jobject obj) {
    jvm = vm;
    jenv = env;
    jobj = obj;
    jclass clz = env->GetObjectClass(jobj);
    if(!clz)
    {
        LOGE("get jclass wrong");
        return;
    }
    jmid = env->GetMethodID(clz, "onError", "(ILjava/lang/String;)V");
    if(!jmid)
    {
        LOGE("get jmethodID wrong");
        return;
    }
}

/**
 *
 * @param type  0：env线程 1：子线程
 * @param code
 * @param msg
 */
void WlListener::onError(int type, int code, const char *msg) {
    if(type == 0)
    {
        jstring jmsg = jenv->NewStringUTF(msg);
        jenv->CallVoidMethod(jobj, jmid, code, jmsg);
        jenv->DeleteLocalRef(jmsg);
    }
    else if(type == 1)
    {
        JNIEnv *env;
        jvm->AttachCurrentThread(&env, 0);

        jstring jmsg = env->NewStringUTF(msg);
        env->CallVoidMethod(jobj, jmid, code, jmsg);
        env->DeleteLocalRef(jmsg);

        jvm->DetachCurrentThread();
    }
}
