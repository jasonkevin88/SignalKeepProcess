package com.jason.signal.process;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.Process;
import android.util.Log;

import java.util.Timer;
import java.util.TimerTask;

import androidx.annotation.Nullable;

/**
 * Description:用来做包活的线程
 *
 * @author 陈宝阳
 * @create 2020/6/22 09:55
 */
public class KeepProcessService extends Service {

  private static final String TAG = "BAO";

  private int i = 0;

  @Override
  public void onCreate() {
    super.onCreate();
    ProcessWatcher watcher = new ProcessWatcher();
    watcher.watcher(String.valueOf(Process.myUid()), Process.myPid());

    Timer timer = new Timer();
    timer.scheduleAtFixedRate(new TimerTask() {
      @Override
      public void run() {
        Log.i(TAG, "服务进程，运行中 i = "+i);
        i++;
      }
    }, 1000,  3000);
  }


  @Nullable
  @Override
  public IBinder onBind(Intent intent) {
    return null;
  }


}
