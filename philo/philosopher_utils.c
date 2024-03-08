/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:51:18 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/08 16:52:30 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Simple routine to unlock forks
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_forks_release_right_first(t_philo *philo)
{
	pthread_mutex_lock(philo->right_sfgrd);
	pthread_mutex_lock(philo->left_sfgrd);
	*philo->left_fork = 0;
	*philo->right_fork = 0;
	pthread_mutex_unlock(philo->right_sfgrd);
	pthread_mutex_unlock(philo->left_sfgrd);
}

void	ft_forks_release_left_first(t_philo *philo)
{
	pthread_mutex_lock(philo->left_sfgrd);
	pthread_mutex_lock(philo->right_sfgrd);
	*philo->left_fork = 0;
	*philo->right_fork = 0;
	pthread_mutex_unlock(philo->left_sfgrd);
	pthread_mutex_unlock(philo->right_sfgrd);
}

/// @brief Prints message that philosopher eats and when
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_print_eat_and_delay(t_philo *philo, int p_num)
{
	pthread_mutex_lock(philo->print);
	if (ft_death_check(philo))
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	printf("%llu %i is eating\n", (ft_get_time() - *philo->start_time),
		p_num + 1);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->eat);
	pthread_mutex_lock(philo->data_mut);
	philo->ate++;
	pthread_mutex_unlock(philo->data_mut);
}

/// @brief Updates stats, last eating and number of meals, and calls for delay
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_eat_dealy_and_stat_update(t_philo *philo, int p_num)
{
	pthread_mutex_lock(philo->data_mut);
	if (!philo->state)
	{
		pthread_mutex_unlock(philo->data_mut);
		return ;
	}
	philo->last_eating = ft_get_time();
	pthread_mutex_unlock(philo->data_mut);
	ft_print_eat_and_delay(philo, p_num);
}

/// @brief Prints message that philosopher sleeps and when
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_print_take_fork(t_philo *philo, int p_num)
{
	pthread_mutex_lock(philo->print);
	if (ft_death_check(philo))
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	printf("%llu %i has taken a fork\n", (ft_get_time()
			- *philo->start_time), p_num + 1);
	pthread_mutex_unlock(philo->print);
}
