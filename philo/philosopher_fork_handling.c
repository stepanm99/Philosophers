/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_fork_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:51:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/02/09 22:50:27 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Function that locks forks for philosopher, taking right first
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_right_first_fork_lock(t_data *data, int p_num)
{
	if (ft_check_state(data, p_num))
		return ;
	while (1)
	{
		pthread_mutex_lock(data->philos[p_num].right_sfgrd);
		if (!*data->philos[p_num].right_fork)
			*data->philos[p_num].right_fork = 1;
		pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
		pthread_mutex_lock(data->philos[p_num].left_sfgrd);
		if (!*data->philos[p_num].left_fork)
		{
			*data->philos[p_num].left_fork = 1;
			if (!ft_check_state(data, p_num))
				ft_print_take_fork(data, p_num);
			pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
			break ;
		}
		else
			*data->philos[p_num].right_fork = 0;
		pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
		ft_usleep(data->eat / 12);
	}
}

/// @brief Function that locks forks for philosopher, taking left first
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_left_first_fork_lock(t_data *data, int p_num)
{
	if (ft_check_state(data, p_num))
		return ;
	while (1)
	{
		pthread_mutex_lock(data->philos[p_num].left_sfgrd);
		if (!*data->philos[p_num].left_fork)
			*data->philos[p_num].left_fork = 1;
		pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
		pthread_mutex_lock(data->philos[p_num].right_sfgrd);
		if (!*data->philos[p_num].right_fork)
		{
			*data->philos[p_num].right_fork = 1;
			if (!ft_check_state(data, p_num))
				ft_print_take_fork(data, p_num);
			pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
			break ;
		}
		else
			*data->philos[p_num].left_fork = 0;
		pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
		ft_usleep(data->eat / 8);
	}
}
