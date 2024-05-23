#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int tmp = 200000;

void *tread1_islem(void *thread_arg)
{
    pthread_mutex_lock(&mutex);

    tmp /= 1000; 
    printf("thread1 islemi tamamlandı degiskenin yeni degeri :%d\n", tmp);

    pthread_mutex_unlock(&mutex);

    return(NULL);
}

void *thread2_islem(void *thread_arg)
{
    pthread_mutex_lock(&mutex);

    tmp /= 100;
    printf("thread2 islemi tamamlandı degiskenin yeni degeri :%d\n", tmp);

    pthread_mutex_unlock(&mutex);

    return(NULL);
}


int main()
{
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &tread1_islem, NULL);
    pthread_create(&thread2, NULL, &thread2_islem, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("islemler tamamlandi tmp yeni degeri :%d\n", tmp);
    return(0);
}