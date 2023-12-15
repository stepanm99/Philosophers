#include<pthread.h>
#include<stdio.h>

void	*ft_thread(void *arg)
{
	int	n;

	n = *(int *)arg;
	printf("Number from a thread: %i\n", n);
}

int	main(void)
{
	pthread_t	thread;
	int			n;

	n = 420;
	printf("Hello\n");
	pthread_create(&thread, NULL, ft_thread, (void *)&n);
	pthread_exit(NULL);

}
