package com.ywl532.jnithread;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

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
}
