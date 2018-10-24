#include<stdlib.h> 
#include<stdio.h> 
#include "../src/logger.h" 
#include<unistd.h>  
#include<stdint.h> 
#include<math.h> 
#include<time.h> 
#include<pthread.h>


void *test_self(void *x) {
    char *joker = (char *)x; 
    static const enum LOG_TYPE log_types_a[8] = {EMERGENCY, ALERT, CRITICAL, ERRROR, WARNING, NOTICE, INFO, DEBUG}; 
    for(uint64_t i = 0; i < 900000; i++) {
            LOG(log_types_a[(int)(rand()%8)], joker);  
    } 
} 

int main() {
    //log_init(NULL);
    log_init("logs/venom/"); 
    srand(time(NULL));
    const char * joker = "why so serious?";
 
    static const enum LOG_TYPE log_types_a[8] = { EMERGENCY, ALERT, CRITICAL, ERRROR, WARNING, NOTICE, INFO, DEBUG}; 
    pthread_t thread,thread2,thread3,thread4,thread5;

    pthread_create(&thread, NULL, test_self, (void*)joker); 
    pthread_create(&thread2, NULL, test_self, (void*)joker); 
    pthread_create(&thread3, NULL, test_self, (void*)joker); 
    pthread_create(&thread4, NULL, test_self, (void*)joker); 
    pthread_create(&thread5, NULL, test_self, (void*)joker); 

    char *joker2 = "from the main thread"; 
    for(uint64_t i = 0; i < 900000; i++) {
       LOG(log_types_a[(int)(rand()%8)], joker2);  
    }
    
    

    pthread_join(thread, NULL); 
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL); 

    return 0; 
} 
