/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:05:04 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/01 22:40:33 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Prints error message, frees allocated memory and exits
/// @param data pointer to main data struct
/// @param errno what kind of error will be shown
void	ft_error(t_data *data, int errno)
{
	if (data)
		ft_free_data(data, errno);
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

void	ft_single_philo(t_data *data)
{
	ft_usleep(data->die);
	printf("%i 0 died\n", data->die);
	ft_free_data(data, 2);
	exit(0);
}
