/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:46:35 by smelicha          #+#    #+#             */
/*   Updated: 2024/02/14 01:47:21 by smelicha         ###   ########.fr       */
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
