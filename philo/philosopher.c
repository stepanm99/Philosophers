/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:39:08 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/04 23:46:40 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Eat routine
/// @param data Main data struct
/// @param p_num Number of philosopher
/// @return 1 if eating successfull, 0 if philo died
char	ft_eat(t_philo *philo, int p_num)
{
	if (ft_death_check(philo))
		return (0);
	if (!(p_num % 2))
		ft_right_first_fork_lock(philo, p_num);
	else
		ft_left_first_fork_lock(philo, p_num);
	if (ft_death_check(philo))
		return (0);
	ft_eat_dealy_and_stat_update(philo, p_num);
	if (!(p_num % 2))
		ft_forks_release_right_first(philo);
	else
		ft_forks_release_left_first(philo);
	ft_sleep(philo, p_num);
	return (1);
}

/// @brief Sleep routine
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_sleep(t_philo *philo, int p_num)
{
	if (ft_death_check(philo))
		return ;
	pthread_mutex_lock(philo->print);
	printf("%lu %i is sleeping\n", (ft_get_time() - *philo->start_time),
		p_num + 1);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->sleep);
	ft_think(philo, p_num);
}

/// @brief Thinking routine
/// @param data Main data struct
/// @param p_num Number of philosopher
void	ft_think(t_philo *philo, int p_num)
{
	if (ft_death_check(philo))
		return ;
	pthread_mutex_lock(philo->print);
	printf("%lu %i is thinking\n", (ft_get_time() - *philo->start_time),
		p_num + 1);
	pthread_mutex_unlock(philo->print);
}

/// @brief Check if the philo is still alive
/// @param data Main data struct
/// @param p_num Number of philosopher
/// @return 1 if dead, 0 if alive
char	ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(philo->data_mut);
	if (philo->state == 0)
	{
		pthread_mutex_unlock(philo->data_mut);
		return (1);
	}
	if ((ft_get_time() - philo->last_eating) > (uint64_t)philo->die)
	{
		philo->state = 0;
		pthread_mutex_unlock(philo->data_mut);
		return (1);
	}
	pthread_mutex_unlock(philo->data_mut);
	return (0);
}



/// @brief Routine of a single philosopher
/// @param data Main struct where philosopher finds own data
/// @param p_num Number of philosopher, used to acces OWN data from array
void	*ft_philosopher(void *arg_ptr)
{
	t_philo_arg	*arg;
	t_philo		*philo;
	int			p_num;
	char		eat_return;

	arg = (t_philo_arg *)arg_ptr;
	philo = arg->philo;
	p_num = arg->p_num;
	eat_return = 1;
	pthread_mutex_lock(philo->data_mut);
	philo->state = 1;
	pthread_mutex_unlock(philo->data_mut);
	// pthread_mutex_lock(philo->print);
	// printf("(philo->eat / 2) * (p_num %% 2) is %lu\n", (uint64_t)((philo->eat / 2) * (p_num % 2)));
	// pthread_mutex_unlock(philo->print);
	ft_wait_for_start_time(philo->start_time, philo->print);
	ft_synchro_start((*philo->start_time + (uint64_t)((philo->eat / 2) * (p_num % 2))));
	// pthread_mutex_lock(philo->print);
	// printf("After synchro start\n");
	// pthread_mutex_unlock(philo->print);
	philo->last_eating = *philo->start_time;
	while (1)
	{
		// pthread_mutex_lock(philo->print);
		// printf("eat_return: %i\n", eat_return);
		// pthread_mutex_unlock(philo->print);
		if (eat_return)
			eat_return = ft_eat(philo, philo->number);
		else
			break ;
	}
	return (NULL);
}
