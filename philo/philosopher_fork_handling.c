/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_fork_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:51:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/02/27 18:26:41 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Function that locks forks for philosopher, taking right first
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_right_first_fork_lock(t_data *data, int p_num)
{
	while (1)
	{
		if (ft_check_state(data, p_num))
			return ;
		pthread_mutex_lock(&data->print);
		if (*data->philos[p_num].left_fork == 0 
			&& *data->philos[p_num].right_fork == 0)
		{
			*data->philos[p_num].left_fork = 1;
			ft_print_take_fork(data, p_num);
			*data->philos[p_num].right_fork = 1;
			pthread_mutex_unlock(&data->print);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&data->print);
		}
		ft_usleep(data->eat / 10);
	}
}

/// @brief Function that locks forks for philosopher, taking left first
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_left_first_fork_lock(t_data *data, int p_num)
{
	while (1)
	{
		if (ft_check_state(data, p_num))
			return ;
		pthread_mutex_lock(&data->print);
		if (*data->philos[p_num].left_fork == 0
			&& *data->philos[p_num].right_fork == 0)
		{
			*data->philos[p_num].left_fork = 1;
			ft_print_take_fork(data, p_num);
			*data->philos[p_num].right_fork = 1;
			pthread_mutex_unlock(&data->print);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&data->print);
		}
		ft_usleep(data->eat / 10);
	}
}
