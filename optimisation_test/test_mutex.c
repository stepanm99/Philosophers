/*
Program to test how much time in microseconds does it take to lock
and unlock mutex with optional number of threads. Output is average
of 10 samples from each thread.
*/
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<stdint.h>

/*
Definitions
*/

typedef struct s_data	t_data;
int			thread(void *arg);
uint64_t	ft_get_time(void);
uint64_t	ft_get_utime(void);

typedef struct s_main{
	pthread_t		*tiddies;
	t_data			*threddies;
	pthread_mutex_t	*mutties;
	pthread_mutex_t	main_mut;
	int				total_runs;
	int				number_of_threads;
	const char		*number_from_argument;
}	t_main;

typedef struct s_data{
	pthread_mutex_t	*main_mut;
	pthread_mutex_t	*own_mut;
	pthread_mutex_t	*ready_mut;
	t_main			*main;
	int				id;
	int				ready;
}	t_data;

/*
Tested functions
*/


/*
Util functions
*/

void	ft_usleep(uint64_t delay)
{
	uint64_t	start;

	start = ft_get_utime();
	while ((ft_get_utime() - start) < delay)
		usleep(1);
}

//returns miliseconds
uint64_t	ft_get_time(void)
{
	struct timeval	t;

	if (!gettimeofday(&t, NULL))
		return ((uint64_t)((t.tv_sec * 1000) + (t.tv_usec / 1000)));
	else
		return (0);
}

//returns microseconds
uint64_t	ft_get_utime(void)
{
	struct timeval	t;

	if (!gettimeofday(&t, NULL))
		return ((uint64_t)((t.tv_sec * 1000000) + t.tv_usec));
	else
		return (0);
}

/*
Data preparation and cleaning
*/
void	free_data(t_main *main)
{
	if (main->tiddies)
		free(main->tiddies);
	if (main->threddies)
		free(main->threddies);
	if (main->mutties)
		free(main->mutties);
	free(main);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	num;
	int	multiplier;

	i = 0;
	j = 0;
	num = 0;
	multiplier = 1;
	while (str[i])
		i++;
	while(i)
	{
		multiplier *= 10;
		i--;
	}
	while (str[i])
	{
		multiplier /= 10;
		num += (str[i] - '0') * multiplier;
		i++;
	}

	return (num);
}

void	create_mutexes(t_main *main)
{
	int	i;
	int	number_of_threads = main->number_of_threads;

	i = 0;
	pthread_mutex_init(&main->main_mut, NULL);
	while (i != number_of_threads)
	{
		pthread_mutex_init(&main->mutties[i], NULL);
		i++;
	}
}

void	give_thread_data(t_main *main)
{
	int	i;
	int number_of_threads = main->number_of_threads;

	i = 0;
	while (i != number_of_threads)
	{
		main->threddies[i].id = i;
		main->threddies[i].main_mut = &main->main_mut;
		main->threddies[i].own_mut = &main->mutties[i];
		main->threddies[i].main = main;
		main->threddies[i].ready = 0;
		i++;
	}
}

void	data_prep(t_main *main)
{
	main->total_runs = 0;
	main->mutties = NULL;
	main->threddies = NULL;
	main->tiddies = NULL;
	main->number_of_threads = ft_atoi(main->number_from_argument);
	main->tiddies = malloc(sizeof(pthread_t) * main->number_of_threads);
	if (!main->tiddies)
	{
		free_data(main);
		exit(-1);
	}
	main->threddies = malloc(sizeof(t_data) * main->number_of_threads);
	if (!main->threddies)
	{
		free_data(main);
		exit(-1);
	}
	main->mutties = malloc(sizeof(pthread_mutex_t) * main->number_of_threads);
	if (!main->mutties)
	{
		free_data(main);
		exit(-1);
	}
	create_mutexes(main);
	give_thread_data(main);
}

void	destroy_mutexes(t_main *main)
{
	int	i;

	i = 0;
	while (i != main->number_of_threads)
	{
		pthread_mutex_destroy(&main->mutties[i]);
		i++;
	}
	pthread_mutex_destroy(&main->main_mut);
}

/*
Thread creation
*/

void	wait_for_thread(t_main *main, int number_of_thread)
{
	while (1)
	{
		pthread_mutex_lock(&main->mutties[number_of_thread]);
		if (main->threddies[number_of_thread].ready)
		{
			pthread_mutex_unlock(&main->mutties[number_of_thread]);
			break;
		}
		pthread_mutex_unlock(&main->mutties[number_of_thread]);
		usleep(10);
	}
}

void	create_threads(t_main *main)
{
	int	i;
	int	number_of_htreads;

	i = 0;
	number_of_htreads = main->number_of_threads;
	while (i != number_of_htreads)
	{
		pthread_create(&main->tiddies[i], NULL, (void *)thread, &main->threddies[i]);
		wait_for_thread(main, i);
		i++;
	}
}

/*
Thread function
*/
int	thread(void *arg)
{
	int				i;
	uint64_t		timer_start;
	uint64_t		timer_end;
	uint64_t		cummulative_delay_lock;
	uint64_t		cummulative_delay_unlock;
	t_data			*data;

	data = (t_data *)arg;
	timer_start = 0;
	timer_end = 0;
	cummulative_delay_lock = 0;
	cummulative_delay_unlock = 0;
	pthread_mutex_lock(data->own_mut);
	data->ready = 1;
	pthread_mutex_unlock(data->own_mut);
	i = 10;
	while(i)
	{
		pthread_mutex_lock(data->own_mut);
		i--;
		pthread_mutex_unlock(data->own_mut);

		timer_start = ft_get_utime();
		pthread_mutex_lock(data->main_mut);
//		usleep(1);
		timer_end = ft_get_utime();
		cummulative_delay_lock += timer_end - timer_start;
		data->main->total_runs++;
		timer_start = ft_get_utime();
		pthread_mutex_unlock(data->main_mut);
//		usleep(1);
		timer_end = ft_get_utime();
		cummulative_delay_unlock += timer_end - timer_start;
		usleep(1000);
	}
	ft_usleep(100000);
	pthread_mutex_lock(data->main_mut);
	printf("Average delay from %i for lock:\t%lu\tunlock:\t%lu\n", data->id, (cummulative_delay_lock / 10), (cummulative_delay_unlock / 10));
	pthread_mutex_unlock(data->main_mut);
	return (0);
}

/*
Main function
*/

int	main(int argc, const char **argv)
{
	t_main	*main;
	int		i;

	i = 0;
	if (argc != 2)
	{
		printf("No argument :(... Give it number of threads to run!\n");
		return (0);
	}
	main = malloc(sizeof(t_main));
	if (!main)
		return (-1);
	main->number_from_argument = argv[1];
	data_prep(main);
	create_threads(main);
	while (i != main->number_of_threads)
	{
		pthread_join(main->tiddies[i], NULL);
		i++;
	}
	printf("Total runs: %i\n", main->total_runs);
	destroy_mutexes(main);
	free_data(main);
	return (0);
}
