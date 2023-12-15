/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:18 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/15 17:59:31 by smelicha         ###   ########.fr       */
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

int	main(int argc, const char **argv)
{
	t_data	*data;
	
	printf("argc: %i\n", argc);
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		error(data, 1);
	arg_pars(data, argc, argv);
	print_data(data);
	free_data(data);
	return (0);
}