/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:02:27 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/17 23:23:21 by smelicha         ###   ########.fr       */
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
	printf("print mutex |%s| |%li|\n", data->print.__opaque, data->print.__sig);
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
		printf("original time slept: %d\n", ((t2.tv_usec + (suseconds_t)1000000) - t1.tv_usec) / (suseconds_t)1);
	else
		printf("original time slept: %d\n", (t2.tv_usec - t1.tv_usec) / (suseconds_t)1);
	gettimeofday(&t1, NULL);
	ft_usleep(time);
	gettimeofday(&t2, NULL);

	if (t2.tv_sec - t1.tv_sec)
		printf("new time slept: %d\n", ((t2.tv_usec + (suseconds_t)1000000) - t1.tv_usec) / (suseconds_t)1);
	else
		printf("new time slept: %d\n", (t2.tv_usec - t1.tv_usec) / (suseconds_t)1);
}

void	print_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i != data->num_of_philos)
	{
		printf("number of philo: %i, number from philo: %i\n", (i + 1), data->philos[i].number);
		i++;
	}
}