/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:09 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/16 22:49:21 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Call mutex destroy routine to exit cleanly
/// @param data Main data struct
void	ft_destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	while (i != data->num_of_philos)
	{
		pthread_mutex_destroy(&data->fork_safeguard[i]);
		pthread_mutex_destroy(&data->state_mut[i]);
		pthread_mutex_destroy(&data->last_eating_mut[i]);
		pthread_mutex_destroy(&data->ate_mut[i]);
		i++;
	}
}

/// @brief Destroy mutexes and free memory
/// @param data Main data struct
void	ft_free_data(t_data *data)
{
	ft_destroy_mutexes(data);
	if (data->overeaters)
		free(data->overeaters);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->fork_safeguard)
		free(data->fork_safeguard);
	if (data->state_mut)
		free(data->state_mut);
	if (data->last_eating_mut)
		free(data->last_eating_mut);
	if (data->ate_mut)
		free(data->ate_mut);
	if (data)
		free(data);
}

/// @brief Initialize array of forks (mutexes)
/// @param data Main data struct
void	ft_prepare_forks_data(t_data *data)
{
	int	i;

	i = 0;
//	printf("num of philos from prepare forks: %i\n", data->num_of_philos);
	data->forks = malloc(sizeof(char) * data->num_of_philos);
	if (!data->forks)
		ft_error(data, ALLOCATION_ERR);
	data->fork_safeguard = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->fork_safeguard)
		ft_error(data, ALLOCATION_ERR);
	data->state_mut = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->state_mut)
		ft_error(data, ALLOCATION_ERR);
	data->last_eating_mut = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->last_eating_mut)
		ft_error(data, ALLOCATION_ERR);
	data->ate_mut = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->ate_mut)
		ft_error(data, ALLOCATION_ERR);
	while (i != data->num_of_philos)
	{
		data->forks[i] = 0;
		if (pthread_mutex_init(&data->fork_safeguard[i], NULL))
			ft_error(data, MUTEX_ERR);
		if (pthread_mutex_init(&data->state_mut[i], NULL))
			ft_error(data, MUTEX_ERR);
		if (pthread_mutex_init(&data->last_eating_mut[i], NULL))
			ft_error(data, MUTEX_ERR);
		if (pthread_mutex_init(&data->ate_mut[i], NULL))
			ft_error(data, MUTEX_ERR);
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
		data->philos[i].right_sfgrd = &data->fork_safeguard[i - 1];
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].left_sfgrd = &data->fork_safeguard[i];
		data->philos[i].state_mut = &data->state_mut[i];
		data->philos[i].last_eating_mut = &data->last_eating_mut[i];
		data->philos[i].ate_mut = &data->ate_mut[i];
	}
	else
	{
		data->philos[i].right_fork = &data->forks[data->num_of_philos - 1];
		data->philos[i].right_sfgrd = &data->fork_safeguard[data->num_of_philos - 1];
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].left_sfgrd = &data->fork_safeguard[i];
		data->philos[i].state_mut = &data->state_mut[i];
		data->philos[i].last_eating_mut = &data->last_eating_mut[i];
		data->philos[i].ate_mut = &data->ate_mut[i];
	}
}

/// @brief Initialize array of philos with their data
/// @param data Main data struct
void	ft_prepare_philos_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		ft_error(data, ALLOCATION_ERR);
	data->overeaters = malloc(sizeof(char) * data->num_of_philos);
	if (!data->overeaters)
		ft_error(data, ALLOCATION_ERR);
	while (i != data->num_of_philos)
	{
		data->philos[i].thread_id = 0;
		data->philos[i].number = i + 1;
		data->philos[i].last_eating = 2 * data->num_of_philos;
		data->philos[i].ate = 0;
		data->philos[i].state = 0;
		data->overeaters[i] = 0;
		ft_give_philo_forks(data, i);
		i++;
	}
}
