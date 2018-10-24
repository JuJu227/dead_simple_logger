CC=gcc 

LINK=gcc 

.PHONY : all 
all: app 

app : 
	$(CC) -o bin/test example/test.c src/logger.c -lpthread

.PHONY : clean 
clean :
	rm  bin/test 
