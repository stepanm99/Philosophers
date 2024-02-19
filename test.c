#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
#include<signal.h>



/*Pthread mutex structures for linux*/

// typedef union
// {
//   struct __pthread_mutex_s __data;
//   char __size[__SIZEOF_PTHREAD_MUTEX_T];
//   long int __align;
// } pthread_mutex_t;

// struct __pthread_mutex_s
// {
//   int __lock;
//   unsigned int __count;
//   int __owner;
// #ifdef __x86_64__
//   unsigned int __nusers;
// #endif
//   /* KIND must stay at this position in the structure to maintain
//      binary compatibility with static initializers.  */
//   int __kind;
// #ifdef __x86_64__
//   short __spins;
//   short __elision;
//   __pthread_list_t __list;
// # define __PTHREAD_MUTEX_HAVE_PREV      1
// #else
//   unsigned int __nusers;
//   __extension__ union
//   {
//     struct
//     {
//       short __espins;
//       short __eelision;
// # define __spins __elision_data.__espins
// # define __elision __elision_data.__eelision
//     } __elision_data;
//     __pthread_slist_t __list;
//   };
// # define __PTHREAD_MUTEX_HAVE_PREV      0
// #endif
// };



/*Mutex variables test*/

// void	print_mutex_data(pthread_mutex_t mut)
// {
// //	printf("\n\nMutex data:\n");
// 	printf("align = %li\n", mut.__align);
// 	printf("__lock = %u\n", mut.__data.__count);
// 	printf("__elision = %i\n", mut.__data.__elision);
// 	printf("__kind = %i\n", mut.__data.__kind);
// 	printf("__lock = %i\n", mut.__data.__lock);
// 	printf("__nusers = %u\n", mut.__data.__nusers);
// 	printf("__owner = %i\n", mut.__data.__owner);
// 	printf("__spins = %i\n", mut.__data.__spins);
// }
//
// int	main(void)
// {
// 	pthread_mutex_t	mut;
//
// 	pthread_mutex_init(&mut, NULL);
// 	printf("\n\nmutex initialized\n");
// 	print_mutex_data(mut);
// 	pthread_mutex_lock(&mut);
// 	printf("\n\nmutex locked\n");
// 	print_mutex_data(mut);
// 	pthread_mutex_unlock(&mut);
// 	printf("\n\nmutex unlocked\n");
// 	print_mutex_data(mut);
// }

// void	ft_bzero(void *s, size_t l)
// {
// 	size_t	i;
// 	char	*ptr;

// 	ptr = s;
// 	i = 0;
// 	while (l > 0)
// 	{
// 		ptr[i] = '\0';
// 		i++;
// 		l--;
// 	}
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;

// 	ptr = malloc(count * size);
// 	if (!ptr)
// 		return (NULL);
// 	ft_bzero(ptr, (count * size));
// 	return (ptr);
// }

// static int	getlen(int n);
// static int	getdigit(int n, char *ptr, int neg, int l);
// static char	*edge(void);

// char	*ft_itoa(int n)
// {
// 	int		l;
// 	char	*ptr;
// 	int		neg;

// 	neg = 0;
// 	if (n == -2147483648)
// 		return (edge());
// 	if (n < 0)
// 	{
// 		n = (n * (-1));
// 		neg = 1;
// 	}
// 	l = getlen(n);
// 	if (neg)
// 		l++;
// 	ptr = ft_calloc(l + 1, sizeof(char));
// 	if (!ptr)
// 		return (0);
// 	getdigit(n, ptr, neg, l);
// 	return (ptr);
// }

// static int	getlen(int n)
// {
// 	int	len;

// 	len = 0;
// 	if (n == 0)
// 		return (1);
// 	while (n)
// 	{
// 		n = n / 10;
// 		len++;
// 	}
// 	return (len);
// }

// static int	getdigit(int n, char *ptr, int neg, int l)
// {
// 	if (neg)
// 	{
// 		ptr[0] = '-';
// 	}
// 	if (n == 0)
// 		ptr[0] = '0';
// 	ptr[l] = '\0';
// 	while (n > 0)
// 	{
// 		ptr[l - 1] = ((n % 10) + '0');
// 		n = n / 10;
// 		l--;
// 	}
// 	return (0);
// }

// static char	*edge(void)
// {
// 	char	*ptr;

// 	ptr = ft_calloc(12, sizeof(char));
// 	if (!ptr)
// 		return (0);
// 	ptr[11] = '\0';
// 	ptr[0] = '-';
// 	ptr[1] = '2';
// 	ptr[2] = '1';
// 	ptr[3] = '4';
// 	ptr[4] = '7';
// 	ptr[5] = '4';
// 	ptr[6] = '8';
// 	ptr[7] = '3';
// 	ptr[8] = '6';
// 	ptr[9] = '4';
// 	ptr[10] = '8';
// 	return (ptr);
// }

// typedef struct s_test{
// 	pthread_mutex_t	*print;
// 	int				num;
// 	char			*str;
// }	t_test;

// void	thread(void *data_ptr)
// {
// 	t_test	*test;

// 	test = (t_test*)data_ptr;
// 	pthread_mutex_lock(test->print);
// 	printf("message from thread %i with string %s\n", test->num, test->str);
// 	pthread_mutex_unlock(test->print);
// 	sleep(1);
// 	pthread_exit(0);
// }

// static void	create_threads(pthread_t *threads, t_test *test)
// {
// 	int	i;

// 	i = 0;
// 	while (i != 100)
// 	{
// 		pthread_create(&threads[i], NULL, (void *)&thread, &test[i]);
// 		i++;
// 	}
// }

// static void	detach_threads(pthread_t *threads)
// {
// 	int	i;

// 	i = 0;
// 	while (i != 100)
// 	{
// 		pthread_detach(threads[i]);
// 		i++;
// 	}
// }

// static void	print_threads(pthread_t *threads)
// {
// 	int	i;

// 	i = 0;
// 	while (i != 100)
// 	{
// 		printf("thread nr %i has id: %lu\n", i, threads[i]);
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	t_test			*test;
// 	pthread_t		*threads;
// 	pthread_mutex_t	*print;
// 	int		i;

// 	i = 0;
// 	test = NULL;
// 	test = malloc(sizeof(t_test) * 100);
// 	if (!test)
// 	{
// 		printf("malloc error\n");
// 		exit(-1);
// 	}
// 	threads = NULL;
// 	threads = malloc(sizeof(pthread_t) * 100);
// 	if (!threads)
// 	{
// 		printf("malloc error\n");
// 		exit(-1);
// 	}
// 	print = NULL;
// 	print = malloc(sizeof(pthread_mutex_t));
// 	if (!print)
// 	{
// 		printf("malloc error\n");
// 		exit(-1);
// 	}
// 	pthread_mutex_init(print, NULL);
// 	while (i != 100)
// 	{
// 		test[i].num = i;
// 		test[i].str = ft_itoa(i);
// 		test[i].print = print;
// 		i++;
// 	}
// 	create_threads(threads, test);
// 	print_threads(threads);
// 	detach_threads(threads);
// 	sleep(2);
// 	i = 0;
// 	while (i != 100)
// 	{
// //		free(threads[i]);
// 		free(test[i].str);
// 		i++;
// 	}
// 	free(test);
// 	free(print);
// 	free(threads);
// }




// int main(void)
// {
// 	int n;

// 	n = sizeof(int);
// 	printf("size of int: %d\n", n);
// 	n = sizeof(int*);
// 	printf("sizeof in*: %d\n", n);
// 	return (0);
// }



/*

 Here I tested that when thread function returns while there is pthread_join
 function in main, there are no leaks!! Meaning I have to rework
 my dear philosophers to be able to use pthread_join :(.....

 */

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
	usleep(200);
	return (NULL);
}

int	main(void)
{
	pthread_t		thread1;
	pthread_t		thread2;
	pthread_t		*threads;
	struct timeval	t;
	int				n;
	int				m;
	int				i;

	threads = NULL;
	n = 42;
	i = 0;
	threads = malloc(sizeof(pthread_t) * n);
	if (!threads)
		return (-1);
	printf("Hello\n");
	pthread_create(&thread1, NULL, ft_thread, (void *)&n);
	m = 20;
	pthread_create(&thread2, NULL, ft_thread, (void *)&m);
	while (i != n)
	{
		pthread_create(&threads[i], NULL, ft_thread, (void *)&n);
		i++;
	}
	usleep(4800);
	i = 0;
	while (i != n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("n: %i\tm: %i\n", n, m);
	gettimeofday(&t, NULL);
	printf("seconds: %lu microsecunds: %lu\n", t.tv_sec, t.tv_usec);
	free(threads);
	return (0);
}

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
