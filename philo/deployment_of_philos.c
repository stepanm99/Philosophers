/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deployment_of_philos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:40:52 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/28 22:29:11 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Starts philosophers allowed to eat first
/// @param data Main data struct
void	deploy_eaters(t_data *data)
{
	t_philo_arg	arg;
	int	i;
	int	r;

	i = 0;
	r = 0;
	arg.data = data;
	arg.p_num = i;
	if (data->num_of_philos % 2)
	{
		while (i < data->num_of_philos)
		{
			arg.p_num = i;
			r += pthread_create(&data->philos[i].thread_id, NULL, (void *)&philosopher, &arg);
			i += 2;
		}
	}
	else
	{
		while (i < data->num_of_philos)
		{
			arg.p_num = i;
			r += pthread_create(&data->philos[i].thread_id, NULL, (void *)&philosopher, &arg);
			i += 2;
		}
	}
}

/// @brief Starts other philosophers that will wait for the eaters to finish
/// @param data Main data struct
void	deploy_rest(t_data *data)
{
	t_philo_arg	arg;
	int	i;
	int	r;

	i = 1;
	r = 0;
	arg.data = data;
	if (data->num_of_philos % 2)
	{
		while (i < data->num_of_philos)
		{
			arg.p_num = i;
			r += pthread_create(&data->philos[i].thread_id, NULL, (void *)&philosopher, &arg);
			i += 2;
		}
	}
	else
	{
		while (i < data->num_of_philos)
		{
			arg.p_num = i;
			r += pthread_create(&data->philos[i].thread_id, NULL, (void *)&philosopher, &arg);
			i += 2;
		}
	}
}

/// @brief Routine to start the simulation
/// @param data Main data struct
void	deploy_philosophers(t_data *data)
{
	printf("num of philos before deploying threads: %i\n", data->num_of_philos);
	deploy_eaters(data);
	deploy_rest(data);
	printf("num of philos after deploying threads: %i\n", data->num_of_philos);
	pthread_create(&data->grim_reaper, NULL, (void *)&grim_reaper, data);
	pthread_join(data->grim_reaper, NULL);
}
