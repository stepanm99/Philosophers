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

void	ft_print_philos_stomachs(t_data *data)
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

// static void	wait_for_tid(t_data *data)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i != data->num_of_philos)
// 	{
// 		if (!data->philos[i].thread_id)
// 			i = 0;
// 		if ((ft_get_time() - data->start_time) > (uint64_t)data->die)
// 		{
// 			pthread_mutex_lock(&data->print);
// 			printf("Too many philos for this computer :(\n");
// 			pthread_mutex_unlock(&data->print);
// 			ft_funeral(data, 0, 0);
// 		}
// 		i++;
// 		ft_usleep(5);
// 	}
// }

// static void	ft_join_philos(t_data *data)
// {
// 	int	i;
//
// 	i = 0;
// 	wait_for_tid(data);
// 	while (i != data->num_of_philos)
// 	{
// 		printf("from pthread detach i: %i\n", i);
// 		pthread_mutex_lock(&data->print);
// 		printf("joining TID %lu\n", data->philos[i].thread_id);
// 		pthread_mutex_unlock(&data->print);
// 		pthread_join(data->philos[i].thread_id, NULL);
// 		i++;
// 	}
// }

/* Alternative option of detaching philos but not very working*/
// static char	detach_philos(t_data *data)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i != data->num_of_philos)
// 	{
// 		if (data->philos[i].thread_id)
// 		{
// 			pthread_detach(data->philos[i].thread_id);
// 		}
// 		else
// 			return (1);
// 		i++;
// 	}
// 	pthread_mutex_lock(&data->print);
// 	printf("All philos detached!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
// 	pthread_mutex_unlock(&data->print);
// 	return (0);
// }

void	ft_funeral(t_data *data, int carcass_nr, char print)
{
	int				i;
	unsigned long	t_o_d;

	i = 0;
	t_o_d = ft_get_time() - data->start_time;
	if (print)
	{
		pthread_mutex_lock(&data->print);
		printf("%lu %i died\n", t_o_d, carcass_nr);
		pthread_mutex_unlock(&data->print);
	}
	while (i != data->num_of_philos)
	{
		pthread_mutex_lock(&data->state_mut[i]);
		data->philos[i].state = 0;
		pthread_mutex_unlock(&data->state_mut[i]);
		i++;
	}
	return ;
}

char	obesity_alert(t_data *data, int fatty_nr)
{
	int	i;

	i = 0;
//	ft_print_philos_stomachs(data);
	if (!data->overeaters[fatty_nr])
		data->overeaters[fatty_nr] = 1;
	while (1)
	{
		if (!data->overeaters[i])
			return (0);
		if (i == (data->num_of_philos - 1))
		{
			ft_funeral(data, i, 0);
			return (1);
		}
		i++;
	}
}

void	*ft_grim_reaper(t_data *data)
{
	int		i;

	i = 0;
	ft_synchro_start(data);
	ft_usleep(data->die / 2);
	while(1)
	{
		pthread_mutex_lock(&data->last_eating_mut[i]);
		pthread_mutex_lock(&data->state_mut[i]);
		if (((ft_get_time() - data->philos[i].last_eating > (uint64_t)data->die)
			|| !data->philos[i].state) && data->philos[i].state != 2)
		{
			pthread_mutex_unlock(&data->state_mut[i]);
			pthread_mutex_unlock(&data->last_eating_mut[i]);
			ft_funeral(data, i, 1);
			return (NULL);
		}
		pthread_mutex_unlock(&data->state_mut[i]);
		pthread_mutex_unlock(&data->last_eating_mut[i]);
		pthread_mutex_lock(&data->ate_mut[i]);
		if (data->must_eat && data->philos[i].ate >= data->must_eat)
		{
			pthread_mutex_unlock(&data->ate_mut[i]);
			if (obesity_alert(data, i))
				return (NULL) ;
		}
		pthread_mutex_unlock(&data->ate_mut[i]);
		if (i + 1 != data->num_of_philos)
			i++;
		else
			i = 0;
		usleep(data->die / 10);
	}
	return (NULL);
}
