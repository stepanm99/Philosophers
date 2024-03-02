/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:19 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/02 20:21:51 by smelicha         ###   ########.fr       */
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

void	ft_synchro_start(t_data *data, char w_flag)
{
	if (w_flag)
	{
		while (1)
		{
			if ((data->delayed_start) <= ft_get_time())
				break ;
			ft_usleep(10);
		}
	}
	else
	{
		while (1)
		{
			if ((data->start_time) <= ft_get_time())
				break ;
			ft_usleep(10);
		}
	}
}
