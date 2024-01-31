/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deployment_of_philos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:40:52 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/09 13:56:10 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	ft_wait_for_thread(t_data *data, int p_num)
{
	while (1)
	{
		pthread_mutex_lock(&data->state_mut[p_num]);
		if (data->philos[p_num].state != 2)
		{
			pthread_mutex_unlock(&data->state_mut[p_num]);
			break ;
		}
		pthread_mutex_unlock(&data->state_mut[p_num]);
		ft_usleep(50);
	}
}

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

/// @brief Starts philosophers allowed to eat first
/// @param data Main data struct
void	deploy_eaters(t_data *data)
{
	t_philo_arg	arg;
	int	i;

	i = 0;
	arg.data = data;
	arg.p_num = i;
	if (data->num_of_philos % 2)
		ft_even_deploy_loop(data, arg, i);
	else
		ft_odd_deploy_loop(data, arg, i);
}

/// @brief Starts other philosophers that will wait for the eaters to finish
/// @param data Main data struct
void	deploy_rest(t_data *data)
{
	t_philo_arg	arg;
	int	i;

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
	pthread_mutex_lock(&data->print);
	printf("Before pthread_join of Grim\n");
	pthread_mutex_unlock(&data->print);
	pthread_join(data->grim_reaper, NULL);
	pthread_mutex_lock(&data->print);
	printf("After pthread join of Grim\n");
	pthread_mutex_unlock(&data->print);
	return ;
}
