/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepan <stepan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:51:18 by smelicha          #+#    #+#             */
/*   Updated: 2024/02/28 21:15:40 by stepan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Checks if the philosopher wasn't deemed dead by Grim
/// @param data Main data struct
/// @param p_num Number of philosopher
/// @return 0 if alive, 1 if dead
char	ft_check_state(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	if (data->philos[p_num].state)
	{
		pthread_mutex_unlock(&data->print);
		return (0);
	}
	pthread_mutex_unlock(&data->print);
	return (1);
}

/// @brief Simple routine to unlock forks
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_forks_unlock(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	*data->philos[p_num].left_fork = 0;
	*data->philos[p_num].right_fork = 0;
	pthread_mutex_unlock(&data->print);
}

/// @brief Prints message that philosopher eats and when
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_print_eat_and_delay(t_data *data, int p_num)
{
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->print);
	printf("%lu %i is eating\n", (ft_get_time() - data->start_time),
		p_num + 1);
	pthread_mutex_unlock(&data->print);
	ft_usleep(data->eat);
	pthread_mutex_lock(&data->print);
	data->philos[p_num].ate++;
	pthread_mutex_unlock(&data->print);
}

/// @brief Updates stats, last eating and number of meals, and calls for delay
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_eat_dealy_and_stat_update(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	if (data->philos[p_num].state)
		data->philos[p_num].state = 2;
	else
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	ft_print_eat_and_delay(data, p_num);
	pthread_mutex_lock(&data->print);
	data->philos[p_num].last_eating = ft_get_time();
	if (data->philos[p_num].state)
		data->philos[p_num].state = 1;
	else
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	pthread_mutex_unlock(&data->print);
}

/// @brief Prints message that philosopher sleeps and when
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_print_take_fork(t_data *data, int p_num)
{
	printf("%lu %i has taken a fork\n", (ft_get_time()
			- data->start_time), p_num + 1);
}
