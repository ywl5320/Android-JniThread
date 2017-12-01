#include <jni.h>

#include "AndroidLog.h"
#include "pthread.h"
#include "unistd.h"
#include "queue"

//1、一般线程
pthread_t pthread;//线程对象
void *threadDoThings(void *data)
{
    LOGD("jni thread do things");
    pthread_exit(&pthread);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ywl5320_jnithread_JniThread_normalThread(JNIEnv *env, jobject instance) {
    // TODO
    LOGD("normal thread");
    //创建线程
    pthread_create(&pthread, NULL, threadDoThings, NULL);

}


//2、线程锁

std::queue<int> queue; //产品队列，里面是int的队列
pthread_t pthread_produc; //生产者线程
pthread_t pthread_customer; //消费者线程
pthread_mutex_t mutex; //线程锁
pthread_cond_t cond; //条件对象


void *ptoducThread(void *data)
{
    while(queue.size() < 50)
    {
        LOGD("生产者生产一个产品");
        pthread_mutex_lock(&mutex); //操作队列前先加锁
        queue.push(1);
        if(queue.size() > 0)
        {
            LOGD("生产者通知消费者有产品产生，产品数量为：%d", queue.size());
            pthread_cond_signal(&cond); //有了产品通知消费者
        }
        pthread_mutex_unlock(&mutex); //解锁线程
        sleep(4); //休息4秒，单位是秒
    }
    pthread_exit(&pthread_produc);
}

void *customerThread(void *data)
{
    char *prod = (char *) data;
    LOGD("%", prod);
    while(1) //这里用死循环，时间情况应该给一个变量来控制跳出循环
    {
        pthread_mutex_lock(&mutex); //操作队列前先加锁
        if(queue.size() > 0)
        {
            queue.pop();
            LOGE("消费者消费一个产品，产品数量为：%d", queue.size());
        } else{
            LOGE("产品消费完了，等待生产者生产......");
            pthread_cond_wait(&cond, &mutex); //阻塞线程等待生产者的通知
        }
        pthread_mutex_unlock(&mutex);//解锁线程
        usleep(500 * 1000); //休息0.5秒，usleep单位是微妙
    }
    pthread_exit(&pthread_customer);
}

void initMutex()
{
    pthread_mutex_init(&mutex, NULL); //初始化锁对象 对应pthread_mutex_destroy销毁锁对象
    pthread_cond_init(&cond, NULL); //初始化条件变量 对应pthread_cond_destroy销毁条件变量
    pthread_create(&pthread_produc, NULL, ptoducThread, (void *) "product"); //创建生产者线程，并传递参数
    pthread_create(&pthread_customer, NULL, customerThread, NULL); //创建消费者线程
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ywl5320_jnithread_JniThread_mutexThread(JNIEnv *env, jobject instance) {
    // TODO
    //初始化时，先往队列中添加10个产品
    for(int i = 0; i < 10; i++)
    {
        queue.push(i);
    }
    initMutex();
}

/*

1、pthread_t :用于声明一个线程对象如：pthread_t thread;
2、pthread_creat :用于创建一个实际的线程如：pthread_create(&pthread,NULL,threadCallBack,NULL);其总共接收4个参数，第一个参数为pthread_t对象，第二个参数为线程的一些属性我们一般传NULL就行，第三个参数为线程执行的函数（ void* threadCallBack(void *data) ），第四个参数是传递给线程的参数是void*类型的既可以传任意类型。
3、pthread_exit :用于退出线程如：pthread_exit(&thread)，参数也可以传NULL。注：线程回调函数最后必须调用此方法，不然APP会退出（挂掉）。
4、pthread_mutex_t :用于创建线程锁对象如：pthread_mutex_t mutex;
5、pthread_mutex_init :用于初始化pthread_mutex_t锁对象如：pthread_mutex_init(&mutex, NULL);
6、pthread_mutex_destroy :用于销毁pthread_mutex_t锁对象如：pthread_mutex_destroy(&mutex);
7、pthread_cond_t :用于创建线程条件对象如：pthread_cond_t cond;
8、pthread_cond_init :用于初始化pthread_cond_t条件对象如：pthread_cond_init(&cond, NULL);
9、pthread_cond_destroy :用于销毁pthread_cond_t条件对象如：pthread_cond_destroy(&cond);
10、pthread_mutex_lock :用于上锁mutex，本线程上锁后的其他变量是不能被别的线程操作的如：pthread_mutex_lock(&mutex);
11、pthread_mutex_unlock :用于解锁mutex，解锁后的其他变量可以被其他线程操作如：pthread_mutex_unlock(&mutex);
12、pthread_cond_signal :用于发出条件信号如：pthread_cond_signal(&mutex, &cond);
13、pthread_cond_wait :用于线程阻塞等待，直到pthread_cond_signal发出条件信号后才执行退出线程阻塞执行后面的操作。

*/