#include <jni.h>
#include <string>
#include "native-lib.h"

const char *_user_id;
int _process_id;

//子进程变成僵尸进程会调用这个方法
void sig_handler(int sino) {

    int status;
    //阻塞式函数
    LOGE("等待死亡信号");
    wait(&status);

    LOGE("创建进程");
    create_child_process();

}


extern "C"
JNIEXPORT void JNICALL
Java_com_jason_signal_process_ProcessWatcher_watcher(JNIEnv *env, jobject thiz, jstring user_id, jint process_id) {
    // TODO: implement watcher()
    /*_user_id = user_id;
    _process_id = process_id;

    //为了防止子进程被弄成僵尸进程
    struct  sigaction sa;
    sa.sa_flags=0;

    sa.sa_handler = sig_handler;
    sigaction(SIGCHLD, &sa, NULL);

    create_child_process();*/

    _user_id = env->GetStringUTFChars(user_id, NULL);
    //为了防止子进程被弄成僵尸进程
    struct  sigaction sa;
    sa.sa_flags=0;

    sa.sa_handler = sig_handler;
    sigaction(SIGCHLD, &sa, NULL);
    create_child_process();
}



//创建子进程
//setsid()函数的作用。一般而言，父进程和子进程都处在一个session当中，父进程是session的领头进程。如果当父进程（领头进程）被杀死之后，那么同一个session中的所有进程都会被杀死，或者成为孤儿进程而被init托管。所以，我们需要让子进程调用setsid()，创建一个新的session并将自己设置为该session的领头进程（若领头进程调用setsid()则没有任何效果）。这样，如果父进程被kill掉，因为他们并不在一个session中，所以子进程仍然可以继续执行。由于session对控制终端的独占性，进程同时与控制终端脱离。

void create_child_process() {

    //创建一个子进程
    /*pid_t pid = fork();

    if(pid < 0) {
        //LOGE("创建子进程失败！");
    } else if(pid > 0 && pid < getppid()) {
        *//*LOGE("这个是父进程！");
        LOGE("进程PID是%d", getpid());
        LOGE("进程PPID是%d", getppid());
        LOGE("进程ID%d", _process_id);
        LOGE("创建的子进程ID：%d", pid);*//*
    } else {  //这边判断是否是子进程，根据创建好的pid是否大于父进程的pid，网上的判断是等于0，但是这个是错误，这边创建好了之后，子进程的pid就是有值了，而且跟主进程的pid是不等值的
        //setsid(); // 为子进程创建一个新的session，然后作为领头的session
        LOGE("创建子进程成功！");
        LOGE("进程PID是%d", getpid());
        LOGE("进程PPID是%d", getppid());
        LOGE("创建的子进程ID：%d", pid);
        create_process_monitor();
        *//*int pid2 = fork();
        LOGE("创建的子进程ID2：%d", pid2);
        if(pid2  == 0 || pid2 > _process_id) // child2
        {

        }*//*
    }*/

    pid_t pid = fork();
//
    if (pid < 0) {

    } else if (pid > 0 && pid < getppid()) {
//父进程
    } else {
        LOGE("子进程开启 ");
//        开启线程轮询
        create_process_monitor();
    }
}

void *thread_fun_signal(void *data) {
    //ppid 表示的是父进程号  pid表示当前进程号
    pid_t pid;
    while((pid = getppid()) != 1) {
        sleep(2);
        LOGE("循环 %d ",pid);
    }
    //父进程等于1  apk被干掉了
    LOGE("重启父进程");
    // 用am命令 启动KeepProcessService，来启动主进程
    execlp("am", "am", "startservice", "--user", _user_id,
           "com.jason.signal.process/com.jason.signal.process.KeepProcessService", (char*)NULL);
}

//相当于java  run方法
void *thread_rt(void *data){
    pid_t pid;
    while ((pid = getppid()) != 1) {
        sleep(2);
        LOGE("循环 %d ",pid);
    }
    //父进程等于1  apk被干掉了
    LOGE("重启父进程");
    execlp("am", "am", "startservice", "--user", _user_id,
           "com.jason.signal.process/com.jason.signal.process.KeepProcessService", (char*)NULL);
}

//创建一个线程，用来处理signal的信号
void create_process_monitor() {

    pthread_t tid;
    pthread_create(&tid, NULL, thread_rt, NULL);

    /*pthread_t  pt_t;
    pthread_create(&pt_t, NULL, thread_fun_signal,  NULL);*/
}