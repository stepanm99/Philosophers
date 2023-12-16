/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:18 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/16 02:13:03 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_data(t_data *data)
{
	printf("num_of_philos: %i\n", data->num_of_philos);
	printf("eat: %i\n", data->eat);
	printf("sleep: %i\n", data->sleep);
	printf("die: %i\n", data->die);
	printf("must_eat: %i\n", data->must_eat);
}

int	ft_atoi(const char *str, t_data *data)
{
	size_t	i;
	int		negflag;
	int		n;

	i = 0;
	n = 0;
	negflag = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			error(data, 2);
		if (str[i] == '-')
			negflag = (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * negflag);
}

void	arg_pars(t_data *data, int argc, const char **argv)
{
	if (argv[1])
		data->num_of_philos = ft_atoi(argv[1], data);
	else
		error(data, 2);
	if (argv[2])
		data->die = ft_atoi(argv[2], data);
	else
		error(data, 2);
	if (argv[3])
		data->eat = ft_atoi(argv[3], data);
	else
		error(data, 2);
	if (argv[4])
		data->sleep = ft_atoi(argv[4], data);
	else
		error(data, 2);
	if (argv[5] && argc == 6)
		data->must_eat = ft_atoi(argv[5], data);
}

void	free_data(t_data *data)
{
	if (data)
		free(data);
}

void	error(t_data *data, int errno)
{
	if (data)
		free_data(data);
	if (errno == 2)
	{
		printf("Wrong argument!\n./philo [number of philosophers] ");
		printf("[miliseconds to die] [miliseconds to eat] [miliseconds to");
		printf(" sleep] + optional [how many times to eat]\n");
	}
	else if (errno == 3)
		printf("Error while creating thread\n");
	else if (errno == 1)
		printf("Memory allocation error!\n");
}


// void	ft_usleep(unsigned long time)
// {
// 	struct timeval t1;
// 	struct timeval t2;

// 	gettimeofday(&t1, NULL);
// }

uint64_t	get_time(void)
{
	struct timeval t;

	if (!gettimeofday(&t, NULL))
		return ((t.tv_sec * (uint64_t)1000 + (t.tv_usec / 1000)));
	else
		return (0);
}

void	ft_usleep(uint64_t delay)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < delay)
		usleep(5);
}

void	time_test(int time)
{
	struct timeval t1;
	struct timeval t2;

	printf("\nrequested time: %ius\n", time * 1000);
	gettimeofday(&t1, NULL);
	usleep(time * 1000);
	gettimeofday(&t2, NULL);
	if (t2.tv_sec - t1.tv_sec)
		printf("original time slept: %lu\n", ((t2.tv_usec + 1000000) - t1.tv_usec) / 1);
	else
		printf("original time slept: %lu\n", (t2.tv_usec - t1.tv_usec) / 1);
	gettimeofday(&t1, NULL);
	ft_usleep(time);
	gettimeofday(&t2, NULL);

	if (t2.tv_sec - t1.tv_sec)
		printf("new time slept: %lu\n", ((t2.tv_usec + 1000000) - t1.tv_usec) / 1);
	else
		printf("new time slept: %lu\n", (t2.tv_usec - t1.tv_usec) / 1);
}

void	print_start_time(t_data *data)
{
	printf("start time: %lus %luus\n", data->start->tv_sec, data->start->tv_usec);
}

int	main(int argc, const char **argv)
{
	t_data	*data;
	int		i;
	
	i = 10;
	printf("argc: %i\n", argc);
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		error(data, 1);
	data->start = malloc(sizeof(struct timeval));
	arg_pars(data, argc, argv);
	print_data(data);
	gettimeofday(data->start, NULL);
	print_start_time(data);
	while (i != 200)
	{
		time_test(i);
		i += 10;
	}
	free_data(data);
	return (0);
}