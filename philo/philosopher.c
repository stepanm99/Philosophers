/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:39:08 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/28 18:46:25 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Prints change of state of a given philosopher
/// @param print Mutex to protect printf
/// @param p_number Number of philosopher changing state
/// @param action What is the new state
void	print_status(pthread_mutex_t print, int p_number, int state)
{
	pthread_mutex_lock(&print);
	if (state == 1)
		printf("eating\n");
	if (state == 2)
		printf("sleaping\n");
	if (state == 3)
		printf("thonking\n");
	printf("p_number: %i\n", p_number);
	pthread_mutex_unlock(&print);
}

/// @brief Routine of a single philosopher
/// @param data Main struct where philosopher finds own data
/// @param p_num Number of philosopher, used to acces OWN data from array
void	philosopher(void *arg_ptr)
{
	t_philo_arg	*arg;
	t_data		*data;
	int			p_num;

	arg = (t_philo_arg *)arg_ptr;
	data = arg->data;
	p_num = arg->p_num;

	if (data->print_flag)
		print_status(data->print, p_num, data->philos[p_num].state);
	pthread_mutex_lock(&data->print);
	printf("Philosopher %i deployed at %lims after program started\n", (p_num + 1), (data->start_time - get_time()));
	pthread_mutex_unlock(&data->print);
	data->philos[p_num].state = 0;
	while (1)
		usleep(1000);
}
