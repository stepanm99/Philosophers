/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:39:08 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/14 18:26:21 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_eat(t_data *data, int p_num);
static void	ft_sleep(t_data *data, int p_num);
static void	ft_think(t_data *data, int p_num);
static void	ft_get_forks_r(t_data *data, int p_num);
static void	ft_get_forks_l(t_data *data, int p_num);

static void	ft_print_take_forks(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	printf("%li %i has taken a fork\n", (get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
}

static void	ft_print_eat(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	printf("%li %i is eating\n", (get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
}

/// @brief eat routine
/// @param data 
/// @param p_num 
static void	ft_eat(t_data *data, int p_num)
{
	if (data->philos[p_num].state != 1)
		return ;
	if (!(p_num % 2))
		ft_get_forks_r(data, p_num);
	else
		ft_get_forks_l(data, p_num);
	ft_sleep(data, p_num);
}

/// @brief sleep routine
/// @param data 
/// @param p_num 
static void	ft_sleep(t_data *data, int p_num)
{
	if (data->philos[p_num].state != 2)
		return ;
	pthread_mutex_lock(&data->print);
	printf("%li %i is sleeping\n", (get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	ft_usleep(data->sleep);
	ft_think(data, p_num);
}

static void	ft_think(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	printf("%li %i is thinking\n", (get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	ft_eat(data, p_num);
}

static void	ft_get_forks_r(t_data *data, int p_num)
{
	while (1)
	{
		pthread_mutex_lock(data->philos[p_num].right_sfgrd);
		if (!data->philos[p_num].right_fork->__data.__lock)
			pthread_mutex_lock(data->philos[p_num].right_fork);
		pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
		pthread_mutex_lock(data->philos[p_num].left_sfgrd);
		if (!data->philos[p_num].left_fork->__data.__lock)
		{
			pthread_mutex_lock(data->philos[p_num].left_fork);
			ft_print_take_forks(data, p_num);
			break ;
		}
		else
		{
			pthread_mutex_unlock(data->philos[p_num].right_fork);
		}
		pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
	}
	data->philos[p_num].state = 1;
	ft_print_eat(data, p_num);
	ft_usleep(data->eat);
	data->philos[p_num].ate++;
	data->philos[p_num].last_eating = get_time();
	data->philos[p_num].state = 0;
	pthread_mutex_unlock(data->philos[p_num].left_fork);
	pthread_mutex_unlock(data->philos[p_num].right_fork);
}

static void	ft_get_forks_l(t_data *data, int p_num)
{
	while (1)
	{
		pthread_mutex_lock(data->philos[p_num].left_sfgrd);
		if (!data->philos[p_num].left_fork->__data.__lock)
			pthread_mutex_lock(data->philos[p_num].left_fork);
		pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
		pthread_mutex_lock(data->philos[p_num].right_sfgrd);
		if (!data->philos[p_num].right_fork->__data.__lock)
		{
			pthread_mutex_lock(data->philos[p_num].right_fork);
			ft_print_take_forks(data, p_num);
			break ;
		}
		else
		{
			pthread_mutex_unlock(data->philos[p_num].left_fork);
		}
		pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
	}
	data->philos[p_num].state = 1;
	ft_print_eat(data, p_num);
	ft_usleep(data->eat);
	data->philos[p_num].ate++;
	data->philos[p_num].last_eating = get_time();
	data->philos[p_num].state = 0;
	pthread_mutex_unlock(data->philos[p_num].left_fork);
	pthread_mutex_unlock(data->philos[p_num].right_fork);
}

/// @brief Routine of a single philosopher
/// @param data Main struct where philosopher finds own data
/// @param p_num Number of philosopher, used to acces OWN data from array
void	philosopher(void *arg_ptr)
{
	t_philo_arg	*arg;
	t_data		*data;
	int			p_num;

	arg = (t_philo_arg *)arg_ptr;
	data = arg->data;
	p_num = arg->p_num;
	data->philos[p_num].state = 1;
	ft_usleep(2 * data->num_of_philos);
	ft_eat(data, p_num);
	pthread_exit(NULL);
}
