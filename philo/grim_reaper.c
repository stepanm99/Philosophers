/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:38:01 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/25 21:14:27 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Here will be the code for thread that periodically checks if
somebody has died*/

static void	funeral(t_data *data, int carcass_nr)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->print);
	printf("%i died :(\n", (carcass_nr + 1));
	pthread_mutex_unlock(&data->print);
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
	pthread_mutex_lock(&data->print);
	printf("Grim reaper deployed!\n");
	pthread_mutex_unlock(&data->print);
	while(1)
	{
		if (!data->philos[i].state)
			funeral(data, i);
		if (i + 1 != data->num_of_philos)
			i++;
		else
			i = 0;
		usleep(50);
	}
}
