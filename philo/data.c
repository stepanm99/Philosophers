/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:09 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/03 20:41:50 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Allocates memory for mutexes (forks, safegurds, ...)
/// @param data Main data struct
void	ft_prepare_forks_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		ft_error(data, ALLOCATION_ERR);
	data->overeaters = malloc(sizeof(char) * data->num_of_philos);
	if (!data->overeaters)
		ft_error(data, ALLOCATION_ERR);
	data->forks = malloc(sizeof(char) * data->num_of_philos);
	if (!data->forks)
		ft_error(data, ALLOCATION_ERR);
	data->philo_data_mutex = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->philo_data_mutex)
		ft_error(data, ALLOCATION_ERR);
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->fork_mutex)
		ft_error(data, ALLOCATION_ERR);
	while (i != data->num_of_philos)
	{
		data->forks[i] = 0;
		pthread_mutex_init(&data->philo_data_mutex[i], NULL);
		pthread_mutex_init(&data->fork_mutex[i], NULL);
		i++;
	}
}

/// @brief Gives philosopher acces to forks next to him
/// @param data Main data struct
/// @param i Number of the philosopher's data in array
void	ft_give_philo_forks(t_data *data, int i)
{
	if (i != 0)
	{
		data->philos[i].right_fork = &data->forks[i - 1];
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_sfgrd = &data->fork_mutex[i - 1];
		data->philos[i].left_sfgrd = &data->fork_mutex[i];
	}
	else
	{
		data->philos[i].right_fork = &data->forks[data->num_of_philos - 1];
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_sfgrd = &data->fork_mutex[data->num_of_philos - 1];
		data->philos[i].left_sfgrd = &data->fork_mutex[i];
	}
}

/// @brief Allocates memory for philos, initializes their data
/// @param data Main data struct
void	ft_prepare_philos_data(t_data *data)
{
	int	i;

	i = 0;
	while (i != data->num_of_philos)
	{
		data->philos[i].thread_id = 0;
		data->philos[i].number = i;
		data->philos[i].ate = 0;
		data->philos[i].eat = data->eat;
		data->philos[i].sleep = data->sleep;
		data->philos[i].die = data->die;
		data->philos[i].last_eating = 0;
		data->philos[i].start_time = data->start_time;
		data->philos[i].state = 0;
		data->overeaters[i] = 0;
		data->philos[i].data_mut = &data->philo_data_mutex[i];
		ft_give_philo_forks(data, i);
		i++;
	}
}
