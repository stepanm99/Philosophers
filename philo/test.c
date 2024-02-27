#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct s_data	t_data;
int	thread(void *arg);

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
	t_main			*main;
	int				id;
	int				ready;
}	t_data;

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
		if (main->threddies[number_of_thread].ready)
			break;
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
	t_data			*data;

	data = (t_data *)arg;
	data->ready = 1;
	i = 10000;
	while(i)
	{
		pthread_mutex_lock(data->main_mut);
		data->main->total_runs++;
		pthread_mutex_unlock(data->main_mut);
		pthread_mutex_lock(data->own_mut);
		i--;
		pthread_mutex_unlock(data->own_mut);
	}
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
