/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:05:04 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/18 16:35:30 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

/// @brief Prints error message, frees allocated memory and exits
/// @param data pointer to main data struct
/// @param errno what kind of error will be shown
void	ft_error(t_data *data, int errno)
{
	if (data)
		ft_free_data(data);
	if (errno == 2)
	{
		printf("Wrong argument!\n./philo [number of philosophers] ");
		printf("[miliseconds to die] [miliseconds to eat] [miliseconds to");
		printf(" sleep] + optional [how many times to eat]\n");
	}
	else if (errno == 3)
		printf("Error while creating thread\n");
	else if (errno == 1)
		printf("Memory allocation error!\n");
	else if (errno == 4)
		printf("Mutex initialization error!\n");
	exit(-1);
}
