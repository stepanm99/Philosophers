/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:19 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/04 23:52:30 by smelicha         ###   ########.fr       */
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
		return ((uint64_t)((t.tv_sec * 1000) + (t.tv_usec / 1000)));
	else
		return (0);
}

uint64_t	ft_get_utime(void)
{
	struct timeval	t;

	if (!gettimeofday(&t, NULL))
		return ((uint64_t)((t.tv_sec * 1000000) + t.tv_usec));
	else
		return (0);
}

void	ft_usleep(uint64_t delay)
{
	uint64_t	start;

	delay *= 1000;
	start = ft_get_utime();
	while ((ft_get_utime() - start) < delay)
		usleep(1);
}

void	ft_wait_for_start_time(uint64_t *start_time, pthread_mutex_t *lock)
{
	while (1)
	{
		pthread_mutex_lock(lock);
		if (*start_time != 0)
		{
			pthread_mutex_unlock(lock);
			break ;
		}
		pthread_mutex_unlock(lock);
		ft_usleep(5);
	}
	while (*start_time == 0)
		ft_usleep(5);
}

void	ft_synchro_start(uint64_t start_time)
{
	while (1)
	{
		if (start_time <= ft_get_time())
			break ;
		ft_usleep(10);
	}
}
