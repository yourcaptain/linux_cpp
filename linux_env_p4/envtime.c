#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int main()
{
	int i;
	time_t the_time;

	for(i=0; i<10; i++){
		the_time = time(NULL);
		printf("The time is %ld\n", the_time);
		sleep(2);
	}

	exit(0);
}
