#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>



typedef struct s_data
{
	int	eat;
	int	sleep;
	int	die;
}	t_data;
