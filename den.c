#include <stdio.h>
#include <pthread.h>

// Paylaşılan değişken ve mutex tanımlamaları
int shared_variable = 20000;
pthread_mutex_t mutex;

// İlk iş parçacığı: 10'a bölen
void *divide_by_10(void *arg) {
    // Mutex'i kilitler
    pthread_mutex_lock(&mutex);
    
    // İşlemi gerçekleştirir
    shared_variable /= 10;
    printf("10'a bölündü: %d\n", shared_variable);
    
    // Mutex'i serbest bırakır
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// İkinci iş parçacığı: 100'e bölen
void *divide_by_100(void *arg) {
    // Mutex'i kilitler
    pthread_mutex_lock(&mutex);
    
    // İşlemi gerçekleştirir
    shared_variable /= 100;
    printf("100'e bölündü: %d\n", shared_variable);
    
    // Mutex'i serbest bırakır
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    // Mutex'i başlatır
    pthread_mutex_init(&mutex, NULL);

    // İş parçacıklarını oluşturur
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, divide_by_10, NULL);
    pthread_create(&thread2, NULL, divide_by_100, NULL);

    // İş parçacıklarının tamamlanmasını bekler
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Mutex'i yok eder
    pthread_mutex_destroy(&mutex);

    printf("İşlemler tamamlandı.\n");

    return 0;
}
