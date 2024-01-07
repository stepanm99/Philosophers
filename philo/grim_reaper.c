/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:38:01 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/07 21:12:10 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Here will be the code for thread that periodically checks if
somebody has died*/


static void	print_thread_id(t_data *data)
{
//	int	i;

//	i = 0;
	printf("number of philosophers from print threads: %i\n", data->num_of_philos);
	// while (i < data->num_of_philos)
	// {
	// 	printf("id of thread: %i is %lu\n", i, data->philos[i].thread_id);
	// 	i++;
	// }
}
static void	detach_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i != data->num_of_philos)
	{
//		printf("from pthread detach i: %i\n", i);
		pthread_detach(data->philos[i].thread_id);
		i++;
	}
}

static void	funeral(t_data *data, int carcass_nr)
{
	int	i;

	i = 0;
	carcass_nr = carcass_nr;
	// pthread_mutex_lock(&data->print);
	// printf("%i died :(\n", (carcass_nr + 1));
	// pthread_mutex_unlock(&data->print);
	while (i != data->num_of_philos)
	{
		pthread_cancel(data->philos[i].thread_id);
		i++;
	}
	pthread_exit(NULL);
}

void	grim_reaper(t_data *data)
{
	int	i;

	i = 0;
	// pthread_mutex_lock(&data->print);
	// printf("Grim reaper deployed!\n");
	// pthread_mutex_unlock(&data->print);
	usleep(1000);
	print_thread_id(data);
	detach_philos(data);
//	data->start = 1;
	while(1)
	{
//		printf("state of philo %i is %i\n", i, data->philos[i].state);
		if (!data->philos[i].state)
			funeral(data, i);
		if (i + 1 != data->num_of_philos)
			i++;
		else
			i = 0;
		usleep(data->die / 10);
	}
}
