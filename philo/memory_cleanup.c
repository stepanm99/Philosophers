/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:46:35 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/02 21:38:59 by smelicha         ###   ########.fr       */
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
		pthread_mutex_destroy(&data->philo_data_mutex[i]);
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
}

/// @brief Destroy mutexes and free memory
/// @param data Main data struct
void	ft_free_data(t_data *data, int errno)
{
	if (errno != ARGUMENT_ERR)
		ft_destroy_mutexes(data);
	if (data->overeaters)
		free(data->overeaters);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->philo_data_mutex)
		free(data->philo_data_mutex);
	if (data->fork_mutex)
		free(data->fork_mutex);
	if (data)
		free(data);
}
