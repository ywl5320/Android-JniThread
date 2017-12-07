package com.ywl5320.jnithread;

/**
 * Created by ywl on 2017-11-30.
 */

public class JniThread {

    static
    {
        System.loadLibrary("jnithread");
    }

    //1、一般线程
    public native void normalThread();

    //2、生产者消费者线程
    public native void mutexThread();


    //3、回调线程
    public native void callbackThread();

    private OnErrorListener onErrorListener;

    public void setOnErrorListener(OnErrorListener onErrorListener) {
        this.onErrorListener = onErrorListener;
    }

    //Jni调用此方法，把结果返回到java层
    public void onError(int code, String msg)
    {
        if(onErrorListener != null)
        {
            onErrorListener.onError(code, msg);
        }
    }

    public interface OnErrorListener
    {
        void onError(int code, String msg);
    }

}
