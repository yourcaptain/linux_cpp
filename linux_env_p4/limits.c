#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void work(){
	FILE *f;
	int i;
	double x=4.5;

	f = tmpfile();
	for(i=0; i<10000; i++){
		fprintf(f, "Do some output\n");
		if(ferror(f)){
			fprintf(stderr, "Error writing to temporary file\n");
			exit(1);
		}

		for(i=0; i<10000; i++){
			x = log(x*x + 3.21);
		}
	}
}

int main(){
	struct rusage r_usage;
	struct rlimit r_limit;

	work();
	getrusage(RUSAGE_SELF, &r_usage);

	printf("CPU usage: User=%ld.%08ld, System = %ld.%08ld\n",
		 r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec
		,r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);
}
