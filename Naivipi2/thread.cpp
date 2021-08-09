#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

int sum; /* bien nay dung de chia se du lieu boi cac thread*/
void *runner(void *param); /*khai bao ham chay thread */
int fibonacci(int x);/*khai bao ham Fibonacci*/

int main(int argc, char *argv[])
{
	int count, i;
	pthread_attr_t attr; 

	if (argc != 2) {
		fprintf(stderr,"Su dung: ten_chuong_trinh so_nguyen \n");
		return -1;
	}

	count = atoi(argv[1]);

	if (count < 1) { 
                fprintf(stderr,"%d phai la >= 1\n", count);
		return -1;
	}

	pthread_attr_init(&attr);

	for(i=1;i<=count;i++){
		pthread_t thread;
		pthread_create(&thread,&attr,runner,(void*)i);
		pthread_join(thread,NULL);	
		printf("Fibonacci cua %d la %d\n", i, sum);
	}	
}

void *runner(void *param)
{
	sum = fibonacci((int)param);
	pthread_exit(0);
	return NULL;
}

int fibonacci (int x)
{
    if (x <= 1) {
        return 1;
    }
    return fibonacci(x-1) + fibonacci(x-2);
}
