/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:39:08 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/01 22:38:54 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Eat routine
/// @param data Main data struct
/// @param p_num Number of philosopher
/// @return 1 if eating successfull, 0 if philo died
char	ft_eat(t_data *data, int p_num)
{
	if (ft_death_check(data, p_num))
		return (0);
	if (!(p_num % 2))
		ft_right_first_fork_lock(data, p_num);
	else
		ft_right_first_fork_lock(data, p_num);
	if (ft_death_check(data, p_num))
		return (0);
	ft_eat_dealy_and_stat_update(data, p_num);
	ft_forks_unlock(data, p_num);
	ft_sleep(data, p_num);
	return (1);
}

/// @brief Sleep routine
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_sleep(t_data *data, int p_num)
{
	if (ft_check_state(data, p_num))
		return ;
	pthread_mutex_lock(&data->print);
	printf("%llu %i is sleeping\n", (ft_get_time() - data->start_time),
		p_num + 1);
	pthread_mutex_unlock(&data->print);
	ft_usleep(data->sleep);
	ft_think(data, p_num);
}

/// @brief Thinking routine
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_think(t_data *data, int p_num)
{
	if (ft_check_state(data, p_num))
		return ;
	ft_death_check(data, p_num);
	pthread_mutex_lock(&data->print);
	printf("%llu %i is thinking\n", (ft_get_time() - data->start_time),
		p_num + 1);
	pthread_mutex_unlock(&data->print);
}

/// @brief Check if the philo is still alive
/// @param data Main data struct
/// @param p_num Number of philosopher
/// @return 1 if dead, 0 if alive
char	ft_death_check(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	if (data->philos[p_num].state == 0)
	{
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	if ((ft_get_time() - data->philos[p_num].last_eating) > (uint64_t)data->die)
	{
		data->philos[p_num].state = 0;
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	pthread_mutex_unlock(&data->print);
	return (0);
}

/// @brief Routine of a single philosopher
/// @param data Main struct where philosopher finds own data
/// @param p_num Number of philosopher, used to acces OWN data from array
void	*ft_philosopher(void *arg_ptr)
{
	t_philo_arg	*arg;
	t_data		*data;
	int			p_num;
	char		eat_return;

	arg = (t_philo_arg *)arg_ptr;
	data = arg->data;
	p_num = arg->p_num;
	eat_return = 1;
	pthread_mutex_lock(&data->print);
	data->philos[p_num].state = 1;
	pthread_mutex_unlock(&data->print);
	ft_synchro_start(data, data->philos[p_num].waiter_flag);
	while (1)
	{
		if (eat_return)
			eat_return = ft_eat(data, p_num);
		else
			break ;
	}
	return (NULL);
}
