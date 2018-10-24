#include<string.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<stdint.h> 
#include<fcntl.h> 
#include<sys/stat.h> 
#include<time.h>
#include<stdbool.h>
#include<sys/stat.h> 

#include "logger.h"

#define MAX_PATH_LENGTH 250
#define DEFAULT_LOG_PATH "logs/" 

FILE *logger_fd = NULL; 

extern const char *__progname;

static void clean_up(void){
    if(logger_fd) 
        return; 

    fclose(logger_fd); 
}

static void set_name(char * hot) {
    char * exe_name = (char*)__progname;
    strcat(exe_name,".log");
    strcat(hot,exe_name);
} 

static char *set_time(){ 
    time_t mytime = time(NULL); 
    char * time_str = ctime(&mytime); 
    time_str[strlen(time_str)-1] = '\0'; 
    return time_str; 
}

void LOG(enum LOG_TYPE ltype, const char *msg) { 
    char s[strlen(msg)-1];

    static const char *log_types_a[8] = {"emergency", "alert", "critical","error","warning","notice","info","debug"}; 
    sprintf(s, "%s [ %s ] :%s\n",set_time(),log_types_a[(int)ltype], msg); 
    fwrite(s,1,strlen(s),logger_fd); 
    return; 
} 

void log_init(char *override_path) { 
    if(logger_fd==NULL) {
      atexit(clean_up);
      char path[MAX_PATH_LENGTH]; 
      memset(path,0,MAX_PATH_LENGTH);
      path[MAX_PATH_LENGTH -1] = '\0'; 
      strcpy(path,((override_path !=NULL)?override_path:DEFAULT_LOG_PATH));

      struct stat st ={0};
      if(stat(path, &st) == -1){ 
         mkdir(path, 0777); 
      }
      
      set_name(path);
      logger_fd = fopen(path, "a+");
    }
}
