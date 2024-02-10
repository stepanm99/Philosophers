/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:51:18 by smelicha          #+#    #+#             */
/*   Updated: 2024/02/09 23:00:46 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Checks if the philosopher wasn't deemed dead by Grim
/// @param data Main data struct
/// @param p_num Number of philosopher
/// @return 0 if alive, 1 if dead
char	ft_check_state(t_data *data, int p_num)
{
	pthread_mutex_lock(data->philos[p_num].state_mut);
	if (data->philos[p_num].state)
	{
		pthread_mutex_unlock(data->philos[p_num].state_mut);
		return (0);
	}
	pthread_mutex_unlock(data->philos[p_num].state_mut);
	return (1);
}

/// @brief Simple routine to unlock forks
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_forks_unlock(t_data *data, int p_num)
{
	pthread_mutex_lock(data->philos[p_num].left_sfgrd);
	*data->philos[p_num].left_fork = 0;
	pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
	pthread_mutex_lock(data->philos[p_num].right_sfgrd);
	*data->philos[p_num].right_fork = 0;
	pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
}

/// @brief Prints message that philosopher eats and when
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_print_eat_and_delay(t_data *data, int p_num)
{
	pthread_mutex_unlock(data->philos[p_num].state_mut);
	pthread_mutex_lock(&data->print);
	printf("%lu %i is eating\n", (ft_get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	ft_usleep(data->eat);
	pthread_mutex_lock(data->philos[p_num].ate_mut);
	data->philos[p_num].ate++;
	pthread_mutex_unlock(data->philos[p_num].ate_mut);
}

/// @brief 
/// @param data 
/// @param p_num 
void	ft_eat_dealy_and_stat_update(t_data *data, int p_num)
{
	pthread_mutex_lock(data->philos[p_num].state_mut);
	if (data->philos[p_num].state)
		data->philos[p_num].state = 2;
	else
	{
		pthread_mutex_unlock(data->philos[p_num].state_mut);
		return ;
	}
	ft_print_eat_and_delay(data, p_num);
	pthread_mutex_lock(data->philos[p_num].last_eating_mut);
	data->philos[p_num].last_eating = ft_get_time();
	pthread_mutex_lock(data->philos[p_num].state_mut);
	if (data->philos[p_num].state)
		data->philos[p_num].state = 1;
	else
	{
		pthread_mutex_unlock(data->philos[p_num].state_mut);
		pthread_mutex_unlock(data->philos[p_num].last_eating_mut);
		return ;
	}
	pthread_mutex_unlock(data->philos[p_num].state_mut);
	pthread_mutex_unlock(data->philos[p_num].last_eating_mut);
}

/// @brief Prints message that philosopher sleeps and when
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_print_take_fork(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	printf("%lu %i has taken a fork\n", (ft_get_time()
			- data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
}
