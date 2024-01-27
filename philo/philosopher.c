/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepan <stepan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:39:08 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/20 23:40:31 by stepan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief eat routine
/// @param data 
/// @param p_num 
void	ft_eat(t_data *data, int p_num)
{
	ft_death_check(data, p_num);
	if (!(p_num % 2))
		ft_right_first_fork_lock(data, p_num);
	else
		ft_left_first_fork_lock(data, p_num);
	ft_death_check(data, p_num);
	ft_sleep_and_stat_update(data, p_num);
	ft_forks_unlock(data, p_num);
	ft_sleep(data, p_num);

}

/// @brief sleep routine
/// @param data 
/// @param p_num 
void	ft_sleep(t_data *data, int p_num)
{
	// if (data->philos[p_num].state != 2)
	// 	return ;
	pthread_mutex_lock(&data->print);
	printf("%lu %i is sleeping\n", (get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	ft_usleep(data->sleep);
	ft_think(data, p_num);
}

void	ft_think(t_data *data, int p_num)
{
	ft_death_check(data, p_num);
	pthread_mutex_lock(&data->print);
	printf("%lu %i is thinking\n", (get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	ft_eat(data, p_num);
}

void	ft_death_check(t_data *data, int p_num)
{

	pthread_mutex_lock(&data->print);
	printf("Philo %i checks its death\n", p_num);
	printf("Time since last eating: %lu\n", (get_time() - data->philos[p_num].last_eating));
	pthread_mutex_unlock(&data->print);

	pthread_mutex_lock(data->philos[p_num].state_mut);
	if (data->philos[p_num].state == 0)
	{
		pthread_mutex_unlock(data->philos[p_num].state_mut);
		pthread_mutex_lock(&data->print);
		printf("Philo %i is exiting by itself @ %lu!\n", p_num, (get_time() - data->start_time));
		pthread_mutex_unlock(&data->print);
		exit(0);
// 		while (1)
// 			sleep(1);
	}
	pthread_mutex_lock(data->philos[p_num].last_eating_mut);
	if ((get_time() - data->philos[p_num].last_eating) > (uint64_t)data->die)
	{
		pthread_mutex_unlock(data->philos[p_num].last_eating_mut);
		pthread_mutex_lock(&data->print);
		printf("%i died by itself\n", p_num);
		pthread_mutex_unlock(&data->print);
		data->philos[p_num].state = 0;
		pthread_mutex_unlock(data->philos[p_num].state_mut);
		ft_death_check(data, p_num);
	}
	pthread_mutex_unlock(data->philos[p_num].last_eating_mut);
	pthread_mutex_unlock(data->philos[p_num].state_mut);
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

	pthread_mutex_lock(&data->print);
	printf("Philo %i with TID: %li deployed @ %lu\n", p_num, data->philos[p_num].thread_id,
		   (get_time() - data->start_time));
	pthread_mutex_unlock(&data->print);

	pthread_mutex_lock(data->philos[p_num].state_mut);
	data->philos[p_num].state = 1;
	pthread_mutex_unlock(data->philos[p_num].state_mut);

	ft_synchro_start(data);

	pthread_mutex_lock(&data->print);
	printf("Philo %i started @ %lu!\n", p_num, (get_time() - data->start_time));
	pthread_mutex_unlock(&data->print);

//	ft_usleep(2 * data->num_of_philos);
	ft_eat(data, p_num);
//	pthread_exit(NULL);
}
