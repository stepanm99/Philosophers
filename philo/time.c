/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:19 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/16 23:07:55 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Gets current time since unix epoch in ms
/// @param 
/// @return miliseconds since unix epoch
uint64_t	ft_get_time(void)
{
	struct timeval	t;

	if (!gettimeofday(&t, NULL))
		return ((uint64_t)(t.tv_sec * 1000 + (t.tv_usec / 1000)));
	else
		return (0);
}

void	ft_usleep(uint64_t delay)
{
	uint64_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < delay)
		usleep(5);
}

void	ft_synchro_start(t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("Entered synchro function @ %lu\n", (ft_get_time() - data->start_time));
	pthread_mutex_unlock(&data->print);
	while (1)
	{
		if ((data->start_time) < ft_get_time())
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&data->print);
	printf("Exited synchro function @ %lu\n", (ft_get_time() - data->start_time));
	pthread_mutex_unlock(&data->print);
}
