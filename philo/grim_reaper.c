/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:38:01 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/08 16:52:48 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Prints how many times each philosopher ate
/// @param data Main data struct
void	ft_print_philos_stomachs(t_data *data)
{
	int	i;

	i = 0;
	if (!PRINT_NUMBER_OF_EATS)
		return ;
	while (i != data->num_of_philos)
	{
		pthread_mutex_lock(&data->print);
		pthread_mutex_lock(data->philos[i].ate_mut);
		printf("Philo %i ate %i times\n", i + 1, data->philos[i].ate);
		pthread_mutex_unlock(&data->print);
		pthread_mutex_unlock(data->philos[i].ate_mut);
		i++;
	}
}

/// @brief Procedure to terminate execution of threads to honor the dead philo
/// @param data Main data struct
/// @param carcass_nr Number of dead philosopher
/// @param print flag in case philos die from obesity
void	ft_funeral(t_data *data, int carcass_nr, char print)
{
	int				i;
	unsigned long	t_o_d;

	i = 0;
	t_o_d = ft_get_time() - data->start_time;
	if (print)
	{
		pthread_mutex_lock(&data->print);
		printf("%lu %i died\n", t_o_d, carcass_nr + 1);
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

/// @brief Functions that keep track how obese philos are, if all, then funeral
/// @param data Main data struct
/// @param fatty_nr philosopher which fat layer is examined
/// @return 
char	obesity_alert(t_data *data, int fatty_nr)
{
	int	i;

	i = 0;
	if (!data->overeaters[fatty_nr])
		data->overeaters[fatty_nr] = 1;
	while (1)
	{
		if (!data->overeaters[i])
			return (0);
		if (i == (data->num_of_philos - 1))
		{
			ft_funeral(data, i, 0);
			ft_print_philos_stomachs(data);
			return (1);
		}
		i++;
	}
}

/// @brief Check if the philosopher ate recently and is not starved
/// @param data Main data struct
/// @param i number of examined philo
/// @return 1 when philo starved to death, 0 if philo is OK
static char	ft_check_last_eating(t_data *data, int i)
{
	pthread_mutex_lock(&data->last_eating_mut[i]);
	pthread_mutex_lock(&data->state_mut[i]);
	if (((ft_get_time() - data->philos[i].last_eating > (uint64_t)data->die)
			|| !data->philos[i].state) && data->philos[i].state != 2)
	{
		pthread_mutex_unlock(&data->last_eating_mut[i]);
		pthread_mutex_unlock(&data->state_mut[i]);
		ft_funeral(data, i, 1);
		return (1);
	}
	pthread_mutex_unlock(&data->last_eating_mut[i]);
	pthread_mutex_unlock(&data->state_mut[i]);
	return (0);
}

/// @brief Function of the thread that takes care of the dead
/// @param data Main data struct
/// @return NULL (always)
void	*ft_grim_reaper(t_data *data)
{
	int		i;

	i = 0;
	ft_synchro_start(data, 0);
	ft_usleep(data->die / 2);
	while (1)
	{
		if (ft_check_last_eating(data, i))
			return (NULL);
		pthread_mutex_lock(&data->ate_mut[i]);
		if (data->must_eat && data->philos[i].ate >= data->must_eat)
		{
			pthread_mutex_unlock(&data->ate_mut[i]);
			if (obesity_alert(data, i))
				return (NULL);
		}
		else
			pthread_mutex_unlock(&data->ate_mut[i]);
		if (i + 1 != data->num_of_philos)
			i++;
		else
			i = 0;
		usleep(data->die / 10);
	}
	return (NULL);
}
