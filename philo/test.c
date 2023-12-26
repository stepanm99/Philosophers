#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
#include<signal.h>

void	ft_bzero(void *s, size_t l)
{
	size_t	i;
	char	*ptr;

	ptr = s;
	i = 0;
	while (l > 0)
	{
		ptr[i] = '\0';
		i++;
		l--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

static int	getlen(int n);
static int	getdigit(int n, char *ptr, int neg, int l);
static char	*edge(void);

char	*ft_itoa(int n)
{
	int		l;
	char	*ptr;
	int		neg;

	neg = 0;
	if (n == -2147483648)
		return (edge());
	if (n < 0)
	{
		n = (n * (-1));
		neg = 1;
	}
	l = getlen(n);
	if (neg)
		l++;
	ptr = ft_calloc(l + 1, sizeof(char));
	if (!ptr)
		return (0);
	getdigit(n, ptr, neg, l);
	return (ptr);
}

static int	getlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	getdigit(int n, char *ptr, int neg, int l)
{
	if (neg)
	{
		ptr[0] = '-';
	}
	if (n == 0)
		ptr[0] = '0';
	ptr[l] = '\0';
	while (n > 0)
	{
		ptr[l - 1] = ((n % 10) + '0');
		n = n / 10;
		l--;
	}
	return (0);
}

static char	*edge(void)
{
	char	*ptr;

	ptr = ft_calloc(12, sizeof(char));
	if (!ptr)
		return (0);
	ptr[11] = '\0';
	ptr[0] = '-';
	ptr[1] = '2';
	ptr[2] = '1';
	ptr[3] = '4';
	ptr[4] = '7';
	ptr[5] = '4';
	ptr[6] = '8';
	ptr[7] = '3';
	ptr[8] = '6';
	ptr[9] = '4';
	ptr[10] = '8';
	return (ptr);
}

typedef struct s_test{
	pthread_mutex_t	*print;
	int				num;
	char			*str;
}	t_test;

void	thread(void *data_ptr)
{
	t_test	*test;

	test = (t_test*)data_ptr;
	pthread_mutex_lock(test->print);
	printf("message from thread %i with string %s\n", test->num, test->str);
	pthread_mutex_unlock(test->print);
	while (1)
		sleep(1);
}

int	main(void)
{
	t_test			*test;
	pthread_t		*threads;
	pthread_mutex_t	*print;
	int		i;

	i = 0;
	test = NULL;
	test = malloc(sizeof(t_test) * 100);
	if (!test)
	{
		printf("malloc error\n");
		exit(-1);
	}
	threads = NULL;
	threads = malloc(sizeof(pthread_t) * 100);
	if (!threads)
	{
		printf("malloc error\n");
		exit(-1);
	}
	print = NULL;
	print = malloc(sizeof(pthread_mutex_t));
	if (!print)
	{
		printf("malloc error\n");
		exit(-1);
	}
	pthread_mutex_init(print, NULL);
	while (i != 100)
	{
		test[i].num = i;
		test[i].str = ft_itoa(i);
		test[i].print = print;
		i++;
	}
	i = 0;
	while (i != 100)
	{
		pthread_create(&threads[i], NULL, (void *)&thread, &test[i]);
		i++;
	}
	sleep(2);
	i = 0;
	while (i != 100)
	{
		pthread_kill(threads[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i != 100)
	{
		free(threads[i]);
		free(test[i].str);
		i++;
	}
	free(test);
	free(print);
	free(threads);
}




// int main(void)
// {
// 	int n;

// 	n = sizeof(int);
// 	printf("size of int: %d\n", n);
// 	n = sizeof(int*);
// 	printf("sizeof in*: %d\n", n);
// 	return (0);
// }

// void	*ft_thread(void *arg)
// {
// 	int	n;

// 	n = *(int *)arg;
// 	printf("Number from a thread: %i\n", n);
// 	while (n != 0)
// 	{
// 		printf("Hey, number from the thread: %i\n", n);
// 		n--;
// 	}
// 	n = 0;
// }

// int	main(void)
// {
// 	pthread_t		thread1;
// 	pthread_t		thread2;
// 	struct timeval	t;
// 	int			n;
// 	int			m;

// 	n = 42;
// 	printf("Hello\n");
// 	pthread_create(&thread1, NULL, ft_thread, (void *)&n);
// 	m = 20;
// 	pthread_create(&thread2, NULL, ft_thread, (void *)&m);
// 	usleep(4800000);
// 	printf("n: %i\tm: %i\n", n, m);
// 	gettimeofday(&t, NULL);
// 	printf("seconds: %lu microsecunds: %lu\n", t.tv_sec, t.tv_usec);
// //	pthread_exit(NULL);
// }

// /*odd even test :D*/
// int	main(void)
// {
// 	int	i;

// 	i = 0;
// 	while (i !=50)
// 	{
// 		if (i % 2)
// 			printf("%i is odd\n", i);
// 		else
// 			printf("%i is even\n", i);
// 		i++;
// 	}
// 	return (0);
// }
