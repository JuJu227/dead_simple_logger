#pragma once

#ifndef LOGGER_H  
#define LOGGER_H 

enum LOG_TYPE { EMERGENCY, ALERT, CRITICAL, ERRROR, WARNING, NOTICE, INFO, DEBUG};  
extern enum LOG_TYPE LTYPE; 

void LOG(enum LOG_TYPE,const char *string); 
void log_init(char *override_path); 

#endif 

