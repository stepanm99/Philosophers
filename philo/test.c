#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>

void	*ft_thread(void *arg)
{
	int	n;

	n = *(int *)arg;
	printf("Number from a thread: %i\n", n);
	while (n != 0)
	{
		printf("Hey, number from the thread: %i\n", n);
		n--;
	}
	n = 0;
}

int	main(void)
{
	pthread_t		thread1;
	pthread_t		thread2;
	struct timeval	t;
	int			n;
	int			m;

	n = 42;
	printf("Hello\n");
	pthread_create(&thread1, NULL, ft_thread, (void *)&n);
	m = 20;
	pthread_create(&thread2, NULL, ft_thread, (void *)&m);
	usleep(4800000);
	printf("n: %i\tm: %i\n", n, m);
	gettimeofday(&t, NULL);
	printf("seconds: %lu microsecunds: %lu\n", t.tv_sec, t.tv_usec);
//	pthread_exit(NULL);
}
