package com.jason.signal.process;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

  // 项目的核心原理：就是在应用被杀掉进程的时候，监听系统的signal信号， 利用fork开启一个新的进程，然后再主进程被杀的时候，子进程被init进程托管的时候，重启主进程，保活
  // https://blog.csdn.net/u011279649/article/details/51090369

  // Used to load the 'native-lib' library on application startup.


  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    Intent intent = new Intent(MainActivity.this, KeepProcessService.class);
    startService(intent);
  }


}
