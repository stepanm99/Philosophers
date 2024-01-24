/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:38:01 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/17 20:44:29 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Here will be the code for thread that periodically checks if
somebody has died*/

static void	funeral(t_data *data, int carcass_nr, char print);

static void	print_philos_stomachs(t_data *data)
{
	int	i;

	i = 0;
	while (i != data->num_of_philos)
	{
		pthread_mutex_lock(&data->print);
		printf("Philo %i ate %i times\n", i, data->philos[i].ate);
		pthread_mutex_unlock(&data->print);
		i++;
	}
}

// static void	print_thread_id(t_data *data)
// {
// //	int	i;

// //	i = 0;
// 	printf("number of philosophers from print threads: %i\n", data->num_of_philos);
// 	// while (i < data->num_of_philos)
// 	// {
// 	// 	printf("id of thread: %i is %lu\n", i, data->philos[i].thread_id);
// 	// 	i++;
// 	// }
// }

static void	wait_for_tid(t_data *data)
{
	int	i;

	i = 0;
	while (i != data->num_of_philos)
	{
		if (!data->philos[i].thread_id)
			i = 0;
		if ((get_time() - data->start_time) > (uint64_t)data->die)
		{
			pthread_mutex_lock(&data->print);
			printf("Too many philos for this computer :(\n");
			pthread_mutex_unlock(&data->print);
			funeral(data, 0, 0);
		}
		i++;
		ft_usleep(5);
	}
}

static void	detach_philos(t_data *data)
{
	int	i;

	i = 0;
	wait_for_tid(data);
	while (i != data->num_of_philos)
	{
//		printf("from pthread detach i: %i\n", i);
		pthread_mutex_lock(&data->print);
		printf("detaching TID %lu\n", data->philos[i].thread_id);
		pthread_mutex_unlock(&data->print);
		pthread_detach(data->philos[i].thread_id);
		i++;
	}
}

static void	funeral(t_data *data, int carcass_nr, char print)
{
	int	i;

	i = 0;
	print_philos_stomachs(data);
	if (print)
	{
		pthread_mutex_lock(&data->print);
		printf("%lu %i died\n", (get_time() - data->start_time),
			carcass_nr);
		pthread_mutex_unlock(&data->print);
	}
	while (i != data->num_of_philos)
	{
		//pthread_cancel(data->philos[i].thread_id);
		pthread_mutex_lock(&data->state_mut[i]);
		data->philos[i].state = 0;
		pthread_mutex_unlock(&data->state_mut[i]);
		i++;
	}
	free_data(data);
	exit(0);
}

static void	obesity_alert(t_data *data, int fatty_nr)
{
	int	i;

	i = 0;
	if (!data->overeaters[fatty_nr])
		data->overeaters[fatty_nr] = 1;
	while (1)
	{
		if (!data->overeaters[i])
		{
			pthread_mutex_unlock(&data->print);
			break ;
		}
		if (i == (data->num_of_philos - 1))
		{
			funeral(data, i, 0);
		}
		i++;
	}
}

void	grim_reaper(t_data *data)
{
	int	i;

	i = 0;
//	print_thread_id(data);
	ft_synchro_start(data);
	ft_usleep(data->die / 2);
	detach_philos(data);
//	data->start = 1;
	while(1)
	{
//		printf("state of philo %i is %i\n", i, data->philos[i].state);
		pthread_mutex_unlock(&data->last_eating_mut[i]);
		if ((get_time() - data->philos[i].last_eating > (uint64_t)data->die)
			|| !data->philos[i].state)
		{
			pthread_mutex_unlock(&data->last_eating_mut[i]);
			funeral(data, i, 1);
		}
		pthread_mutex_unlock(&data->last_eating_mut[i]);
		pthread_mutex_lock(&data->ate_mut[i]);
		if (data->must_eat && data->philos[i].ate >= data->must_eat)
		{
			pthread_mutex_unlock(&data->ate_mut[i]);
			obesity_alert(data, i);
		}
		pthread_mutex_unlock(&data->ate_mut[i]);
		if (i + 1 != data->num_of_philos)
			i++;
		else
			i = 0;
		usleep(data->die / 10);
	}
}
