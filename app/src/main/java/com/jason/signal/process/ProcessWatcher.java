package com.jason.signal.process;

/**
 * Description:ProcessWatcher
 *
 * @author 陈宝阳
 * @create 2020/6/22 10:00
 */
public class ProcessWatcher {

  //so库， 这个一定要放在这地方加载，否则，会出现子进程创建问题，导致无法双进程守护
  static {
    System.loadLibrary("native-lib");
  }

  public native void watcher(String userId, int processId);
}
