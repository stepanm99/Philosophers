/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_fork_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:51:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/04 23:01:53 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Function that locks forks for philosopher, taking right first
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_right_first_fork_lock(t_philo *philo, int p_num)
{
	while (1)
	{
		if (ft_death_check(philo))
			return ;
		pthread_mutex_lock(philo->right_sfgrd);
		pthread_mutex_lock(philo->left_sfgrd);
		if (*philo->left_fork == 0 
			&& *philo->right_fork == 0)
		{
			*philo->left_fork = 1;
			ft_print_take_fork(philo, p_num);
			*philo->right_fork = 1;
			pthread_mutex_unlock(philo->left_sfgrd);
			pthread_mutex_unlock(philo->right_sfgrd);
			break ;
		}
		else
		{
			pthread_mutex_unlock(philo->left_sfgrd);
			pthread_mutex_unlock(philo->right_sfgrd);
		}
		ft_usleep(philo->eat / 10);
	}
}

/// @brief Function that locks forks for philosopher, taking left first
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_left_first_fork_lock(t_philo *philo, int p_num)
{
	while (1)
	{
		if (ft_death_check(philo))
			return ;
		pthread_mutex_lock(philo->left_sfgrd);
		pthread_mutex_lock(philo->right_sfgrd);
		if (*philo->left_fork == 0
			&& *philo->right_fork == 0)
		{
			*philo->left_fork = 1;
			ft_print_take_fork(philo, p_num);
			*philo->right_fork = 1;
			pthread_mutex_unlock(philo->left_sfgrd);
			pthread_mutex_unlock(philo->right_sfgrd);
			break ;
		}
		else
		{
			pthread_mutex_unlock(philo->left_sfgrd);
			pthread_mutex_unlock(philo->right_sfgrd);
		}
		ft_usleep(philo->eat / 10);
	}
}
