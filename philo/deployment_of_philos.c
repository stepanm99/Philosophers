/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deployment_of_philos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:40:52 by smelicha          #+#    #+#             */
/*   Updated: 2024/02/09 22:47:04 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Deploys only even philosophers
/// @param data Main data struct
/// @param arg Struct with data for each philo (number and data pointer)
/// @param i Which philosopher to start with
void	ft_even_deploy_loop(t_data *data, t_philo_arg arg, int i)
{
	while (i < data->num_of_philos)
	{
		arg.p_num = i;
		data->philos[i].last_eating = data->start_time;
		data->philos[i].state = 2;
		pthread_create(&data->philos[i].thread_id, NULL,
			(void *)&ft_philosopher, &arg);
		ft_wait_for_thread(data, i);
		i += 2;
	}
}

/// @brief Deploys onle odd philosophers
/// @param data Main data struct
/// @param arg Struct with data for each philo (number and data pointer)
/// @param i Which philosopher to start with
void	ft_odd_deploy_loop(t_data *data, t_philo_arg arg, int i)
{
	while (i < data->num_of_philos)
	{
		arg.p_num = i;
		data->philos[i].last_eating = data->start_time;
		data->philos[i].state = 2;
		pthread_create(&data->philos[i].thread_id, NULL,
			(void *)&ft_philosopher, &arg);
		ft_wait_for_thread(data, i);
		i += 2;
	}
}

/// @brief Starts philosophers that will eat first
/// @param data Main data struct
void	deploy_eaters(t_data *data)
{
	t_philo_arg	arg;
	int			i;

	i = 0;
	arg.data = data;
	arg.p_num = i;
	if (data->num_of_philos % 2)
		ft_even_deploy_loop(data, arg, i);
	else
		ft_odd_deploy_loop(data, arg, i);
}

/// @brief Starts other philosophers
/// @param data Main data struct
void	deploy_rest(t_data *data)
{
	t_philo_arg	arg;
	int			i;

	i = 1;
	arg.data = data;
	arg.p_num = i;
	if (data->num_of_philos % 2)
		ft_even_deploy_loop(data, arg, i);
	else
		ft_odd_deploy_loop(data, arg, i);
}

/// @brief Routine to start the simulation
/// @param data Main data struct
void	ft_deploy_philosophers(t_data *data)
{
	pthread_create(&data->grim_reaper, NULL, (void *)&ft_grim_reaper, data);
	deploy_eaters(data);
	deploy_rest(data);
	pthread_join(data->grim_reaper, NULL);
	return ;
}
