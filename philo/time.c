/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:19 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/11 18:24:52 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Gets current time since unix epoch in ms
/// @return miliseconds since unix epoch
uint64_t	ft_get_time(void)
{
	struct timeval	t;

	if (!gettimeofday(&t, NULL))
		return ((uint64_t)((t.tv_sec * 1000) + (t.tv_usec / 1000)));
	else
		return (0);
}

/// @brief Return unix time with microsecond accuracy
/// @return microseconds since unix epoch
uint64_t	ft_get_utime(void)
{
	struct timeval	t;

	if (!gettimeofday(&t, NULL))
		return ((uint64_t)((t.tv_sec * 1000000) + t.tv_usec));
	else
		return (0);
}

/// @brief Functions holds execution of program for delay miliseconds
/// @param delay number of miliseconds to wait
void	ft_usleep(uint64_t delay)
{
	uint64_t	start;

	delay *= 1000;
	start = ft_get_utime();
	while ((ft_get_utime() - start) < delay)
		usleep(1);
}

/// @brief Function waits until the start time is set, i.e. is not zero
/// @param start_time pointer to memory location of start time variable
/// @param lock mutex that gurads the start time variable
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

/// @brief Waits until the current time is not equal or greater than start time
/// @param start_time future point in time when to exit from this function
void	ft_synchro_start(uint64_t start_time)
{
	while (1)
	{
		if (start_time <= ft_get_time())
			break ;
		ft_usleep(10);
	}
}
