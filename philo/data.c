/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:09 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/02 20:33:00 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Call mutex destroy routine to exit cleanly
/// @param data Main data struct
void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	while (i != data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

/// @brief Destroy mutexes and free memory
/// @param data Main data struct
void	free_data(t_data *data)
{
	destroy_mutexes(data);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data)
		free(data);
}

/// @brief Initialize array of forks (mutexes)
/// @param data Main data struct
void	prepare_forks_data(t_data *data)
{
	int	i;

	i = 0;
	printf("num of philos from prepare forks: %i\n", data->num_of_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		error(data, ALLOCATION_ERR);
	while (i != data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			error(data, MUTEX_ERR);
		i++;
	}
}

/// @brief Gives phlosopher acces to forks next to him
/// @param data Main data struct
/// @param i Number of the philosopher's data in array
void	give_philo_forks(t_data *data, int i)
{
	if (i != 0)
	{
		data->philos[i].right_fork = data->forks[i - 1];
		data->philos[i].left_fork = data->forks[i];
	}
	else
	{
		data->philos[i].right_fork = data->forks[data->num_of_philos - 1];
		data->philos[i].left_fork = data->forks[i];
	}
}

/// @brief Initialize array of philos with their data
/// @param data Main data struct
void	prepare_philos_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		error(data, ALLOCATION_ERR);
	while (i != data->num_of_philos)
	{
		data->philos[i].thread_id = 0;
		data->philos[i].number = i + 1;
		// data->philos[i].eat = data->eat;
		// data->philos[i].sleep = data->sleep;
		// data->philos[i].die = data->die;
		data->philos[i].ate = data->must_eat;
		data->philos[i].state = 1;
//		data->philos[i].number_of_forks = data->num_of_philos;
		data->philos[i].print = data->print;
		give_philo_forks(data, i);
		i++;
	}
}
