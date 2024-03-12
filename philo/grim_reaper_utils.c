/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:01:48 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/06 18:04:28 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Prints how many times each philosopher ate
/// @param data Main data struct
void	ft_print_philos_stomachs(t_data *data)
{
	int	i;

	i = 0;
	if (!PRINT_NUMBER_OF_EATS)
		return ;
	while (i != data->num_of_philos)
	{
		pthread_mutex_lock(&data->print);
		pthread_mutex_lock(&data->philo_data_mutex[i]);
		printf("Philo %i ate %i times\n", i + 1, data->philos[i].ate);
		pthread_mutex_unlock(&data->philo_data_mutex[i]);
		pthread_mutex_unlock(&data->print);
		i++;
	}
}
