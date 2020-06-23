//
// Created by PC-3046 on 2020/6/22.
//

#ifndef SIGNALKEEPPROCESS_NATIVE_LIB_H
#define SIGNALKEEPPROCESS_NATIVE_LIB_H

#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/signal.h>
#include <android/log.h>
#define LOG_TAG "BAO"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

//创建子进程
void create_child_process();

//进程检测
void create_process_monitor();

#endif //SIGNALKEEPPROCESS_NATIVE_LIB_H
