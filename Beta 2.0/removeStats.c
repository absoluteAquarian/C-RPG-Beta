#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

void delay(double dly){
	/* save start time */
    const time_t start = time(NULL);
    time_t current;
    do{
        /* get current time */
        time(&current);
        /* break loop when the requested number of seconds have elapsed */
    }while(difftime(current, start) < dly);
}

int main(){
	int ret = remove("statistics.txt");
	ret = remove("statistics2.txt");
	ret = remove("statistics3.txt");
	ret = remove("statistics4.txt");
	ret = remove("miscstats.txt");
	printf("Done.");
	delay(2);
}