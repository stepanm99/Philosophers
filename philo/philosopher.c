/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:39:08 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/02 20:08:00 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Prints change of state of a given philosopher
/// @param print Mutex to protect printf
/// @param p_number Number of philosopher changing state
/// @param action What is the new state
static void	print_status(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	if (data->philos[p_num].state == 1)
		printf("eating\n");
	if (data->philos[p_num].state == 2)
		printf("sleaping\n");
	if (data->philos[p_num].state == 3)
		printf("thonking\n");
	printf("p_number: %i\n", p_num);
	pthread_mutex_unlock(&data->print);
}

/// @brief eat routine
/// @param data 
/// @param p_num 
static void	ft_eat(t_data *data, int p_num)
{
	if (data->philos[p_num].state != 1)
		return ;
	pthread_mutex_lock(&data->philos[p_num].left_fork);
	pthread_mutex_lock(&data->philos[p_num].right_fork);
	data->philos[p_num].ate++;
	usleep(data->eat * 1000);
	pthread_mutex_unlock(&data->philos[p_num].left_fork);
	pthread_mutex_unlock(&data->philos[p_num].right_fork);
}

/// @brief sleep routine
/// @param data 
/// @param p_num 
static void	ft_sleep(t_data *data, int p_num)
{
	if (data->philos[p_num].state != 2)
		return ;
}

/// @brief checks if the philo is dead
/// @param data 
/// @param p_num 
/// @return 0 if dead, else number of the state
static int	ft_die(t_data *data, int p_num)
{
	if ((get_time() - data->philos[p_num].last_eating) > data->die)
	{
		data->philos[p_num].state = 0;
		print_status(data, p_num);
		return (0);
	}
	else
		return (data->philos[p_num].state);
}

/// @brief Routine of a single philosopher
/// @param data Main struct where philosopher finds own data
/// @param p_num Number of philosopher, used to acces OWN data from array
static void	philosopher(void *arg_ptr)
{
	t_philo_arg	*arg;
	t_data		*data;
	int			p_num;

	arg = (t_philo_arg *)arg_ptr;
	data = arg->data;
	p_num = arg->p_num;
	while (!data->start)
		usleep(50);
	if (data->print_flag)
		print_status(data, p_num);
	pthread_mutex_lock(&data->print);
	printf("Philosopher %i deployed at %lims after program started\n", (p_num + 1), (data->start_time - get_time()));
	pthread_mutex_unlock(&data->print);
	data->philos[p_num].state = 0;
	sleep(1);
	while (data->philos[p_num].state && data->philos[p_num].ate != data->must_eat)
	{
		if (!ft_die(data, p_num))
			break ;
		ft_eat(data, p_num);
		ft_sleep(data, p_num);
	}
	pthread_exit(NULL);
}
