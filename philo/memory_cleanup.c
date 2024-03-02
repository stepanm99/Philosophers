/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:46:35 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/02 21:14:27 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Call mutex destroy routine to exit cleanly
/// @param data Main data struct
void	ft_destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->print);
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
