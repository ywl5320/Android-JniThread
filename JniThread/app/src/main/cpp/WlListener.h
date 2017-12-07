//
// Created by ywl5320
//
#pragma once
#ifndef JNITHREAD_WLLISTENER_H
#define JNITHREAD_WLLISTENER_H

#include <jni.h>

class WlListener {

public:

    JavaVM* jvm;//java虚拟机
    _JNIEnv *jenv;//native线程env对象
    jobject jobj;//全局对象
    jmethodID jmid;//java 方法id,可以根据实际情况创建多个。

public:

    WlListener(JavaVM* vm, _JNIEnv *jenv, jobject obj);
    ~WlListener();

    void onError(int type, int code, const char *msg);

};


#endif //JNITHREAD_WLLISTENER_H
