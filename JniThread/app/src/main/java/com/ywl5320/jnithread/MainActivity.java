package com.ywl5320.jnithread;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    JniThread jniThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jniThread = new JniThread();
        jniThread.setOnErrorListener(new JniThread.OnErrorListener() {
            @Override
            public void onError(int code, String msg) {
                Log.d("ywl5320", "code: " + code + ", msg: " + msg);
                Message message = Message.obtain();
                message.what = code;
                message.obj = msg;
                handler.sendMessage(message);
            }
        });
    }

    public void normalThread(View view) {
        jniThread.normalThread();
    }

    public void mutexThread(View view) {
        jniThread.mutexThread();
    }


    public void jniCallback(View view) {
        jniThread.callbackThread();
    }

    Handler handler = new Handler()
    {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            Toast.makeText(MainActivity.this, (String)msg.obj, Toast.LENGTH_SHORT).show();
        }
    };
}
