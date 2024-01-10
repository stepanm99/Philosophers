/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:39:08 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/10 02:21:54 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	pthread_mutex_lock(&data->print);
	printf("");
	pthread_mutex_unlock(&data->print);
*/



/// @brief checks if the philo is dead
/// @param data 
/// @param p_num 
/// @return 0 if dead, else number of the state
static int	ft_die(t_data *data, int p_num)
{
//	printf("get time - last eating = %li vs ttd: %i from philo: %i\n", (get_time() - data->philos[p_num].last_eating), data->die, p_num);
	if ((get_time() - data->philos[p_num].last_eating) > (uint64_t)data->die)
	{
		data->philos[p_num].state = 0;
		return (0);
	}
	else
		return (data->philos[p_num].state);
}

/// @brief Prints change of state of a given philosopher
/// @param print Mutex to protect printf
/// @param p_number Number of philosopher changing state
/// @param action What is the new state
static void status_print_and_change(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
//	printf("philo %i from status function\n", p_num);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->print);
	if (!ft_die(data, p_num))
		printf("%li %i died\n", (get_time() - data->start_time), p_num);
	if (data->philos[p_num].state == 1)
	{
		printf("%li %i is eating\n", (get_time() - data->start_time), p_num);
		data->philos[p_num].state = 2;
	}
	if (data->philos[p_num].state == 2)
	{
		printf("%li %i is sleeping\n", (get_time() - data->start_time), p_num);
		data->philos[p_num].state = 3;
	}
	if (data->philos[p_num].state == 3)
	{
		printf("%li %i is thinking\n", (get_time() - data->start_time), p_num);
		data->philos[p_num].state = 1;
	}
	pthread_mutex_unlock(&data->print);
}

/// @brief eat routine
/// @param data 
/// @param p_num 
static void	ft_eat(t_data *data, int p_num)
{
	if (data->philos[p_num].state != 1)
		return ;
	while (!data->philos[p_num].left_fork->__data.__lock
		&& !data->philos[p_num].right_fork->__data.__lock)
		usleep(100);
	pthread_mutex_lock(data->philos[p_num].left_fork);
	pthread_mutex_lock(&data->print);
	printf("%li %i has taken a fork\n", (get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(data->philos[p_num].right_fork);
	pthread_mutex_lock(&data->print);
	printf("%li %i has taken a fork\n", (get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	usleep(data->eat * 1000);
	status_print_and_change(data, p_num);
	data->philos[p_num].ate++;
	data->philos[p_num].last_eating = get_time();
	pthread_mutex_unlock(data->philos[p_num].left_fork);
	pthread_mutex_unlock(data->philos[p_num].right_fork);
}

/// @brief sleep routine
/// @param data 
/// @param p_num 
static void	ft_sleep(t_data *data, int p_num)
{
	if (data->philos[p_num].state != 2)
		return ;
	// pthread_mutex_lock(&data->print);
	// printf("philo %i from sleeping function\n", p_num);
	// pthread_mutex_unlock(&data->print);
	status_print_and_change(data, p_num);
	status_print_and_change(data, p_num);
	usleep(data->sleep * 1000);
}

// static void	ft_full(t_data *data, int p_num)
// {
// 	if (data->philos[p_num].ate == data->must_eat &&
// 		data->must_eat != 0)
// 	{
// 		data->philos[p_num].state = 4;
// 		while (1)
// 			usleep(1000000);
// 	}
// }

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
//	while (!data->start)
//		usleep(50);
	pthread_mutex_lock(&data->print);
	printf("Philosopher %i deployed at %lims after program started\n", (p_num + 1), (data->start_time - get_time()));
	pthread_mutex_unlock(&data->print);
	data->philos[p_num].state = 1;
	usleep(2000 * data->num_of_philos);
	while (data->philos[p_num].state) // && data->philos[p_num].ate != data->must_eat
	{
		pthread_mutex_lock(&data->print);
//		printf("Philosopher %i while loop\n", (p_num + 1));
		pthread_mutex_unlock(&data->print);
		// if (!ft_die(data, p_num))
		// 	break ;
		ft_eat(data, p_num);
//		ft_full(data, p_num);
		ft_sleep(data, p_num);
	}
	pthread_mutex_lock(&data->print);
	printf("Philosopher %i finished at %lims after program started\n", (p_num + 1), (data->start_time - get_time()));
	pthread_mutex_unlock(&data->print);
	pthread_exit(NULL);
}
