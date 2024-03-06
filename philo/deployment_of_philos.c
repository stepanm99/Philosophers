/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deployment_of_philos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:40:52 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/06 17:24:20 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Function waits until the thread works, signalled by state != 2
/// @param data Main data struct
/// @param p_num Number of philosopher to wait for
void	ft_wait_for_thread(t_data *data, int p_num)
{
	while (1)
	{
		pthread_mutex_lock(&data->philo_data_mutex[p_num]);
		if (data->philos[p_num].state != 2)
		{
			pthread_mutex_unlock(&data->philo_data_mutex[p_num]);
			break ;
		}
		pthread_mutex_unlock(&data->philo_data_mutex[p_num]);
		ft_usleep(50);
	}
}

/// @brief Routine to start the simulation
/// @param data Main data struct
void	ft_deploy_philosophers(t_data *data)
{
	int			i;
	t_philo_arg	arg;

	arg.data = data;
	i = 0;
	pthread_create(&data->grim_reaper, NULL, (void *)&ft_grim_reaper, data);
	while (i < data->num_of_philos)
	{
		arg.p_num = i;
		arg.philo = &data->philos[i];
		pthread_create(&data->philos[i].thread_id, NULL,
			(void *)&ft_philosopher, &arg);
		ft_wait_for_thread(data, i);
		i++;
	}
	pthread_mutex_lock(&data->print);
	data->start_time = ft_get_time() + 50;
	pthread_mutex_unlock(&data->print);
	pthread_join(data->grim_reaper, NULL);
	return ;
}
