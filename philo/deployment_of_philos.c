/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deployment_of_philos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:40:52 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/04 23:52:37 by smelicha         ###   ########.fr       */
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
		pthread_create(&data->philos[i].thread_id, NULL,
			(void *)&ft_philosopher, &arg);
		ft_wait_for_thread(data, i);
		i++;
	}
	data->start_time = ft_get_time() + 50;
	pthread_join(data->grim_reaper, NULL);
	return ;
}
