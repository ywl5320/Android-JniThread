package com.ywl5320.jnithread;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    JniThread jniThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jniThread = new JniThread();
    }

    public void normalThread(View view) {
        jniThread.normalThread();
    }

    public void mutexThread(View view) {
        jniThread.mutexThread();
    }
}
