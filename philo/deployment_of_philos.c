/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deployment_of_philos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:40:52 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/02 20:24:59 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		data->philos[i].last_eating = data->start_time;
		data->philos[i].state = 2;
		data->philos[i].waiter_flag = i % 2;
		pthread_create(&data->philos[i].thread_id, NULL,
			(void *)&ft_philosopher, &arg);
		ft_wait_for_thread(data, i);
		i++;
	}
	pthread_join(data->grim_reaper, NULL);
	return ;
}
