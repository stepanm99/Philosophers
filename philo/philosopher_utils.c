#include "philosophers.h"

void	ft_forks_unlock(t_data *data, int p_num)
{
	pthread_mutex_lock(data->philos[p_num].left_sfgrd);
	*data->philos[p_num].left_fork = 0;
	pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
	pthread_mutex_lock(data->philos[p_num].right_sfgrd);
	*data->philos[p_num].right_fork = 0;
	pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
}

void	ft_sleep_and_stat_update(t_data *data, int p_num)
{
	pthread_mutex_lock(data->philos[p_num].state_mut);
	if (data->philos[p_num].state)
		data->philos[p_num].state = 2;
	else
	{
		pthread_mutex_unlock(data->philos[p_num].state_mut);
		return ;
	}
	pthread_mutex_unlock(data->philos[p_num].state_mut);
	pthread_mutex_lock(&data->print);
	printf("%lu %i is eating\n", (ft_get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	ft_usleep(data->eat);
	pthread_mutex_lock(data->philos[p_num].ate_mut);
	data->philos[p_num].ate++;
	pthread_mutex_unlock(data->philos[p_num].ate_mut);
	pthread_mutex_lock(data->philos[p_num].last_eating_mut);
	data->philos[p_num].last_eating = ft_get_time();
	pthread_mutex_lock(data->philos[p_num].state_mut);
	if (data->philos[p_num].state)
		data->philos[p_num].state = 1;
	else
	{
		pthread_mutex_unlock(data->philos[p_num].state_mut);
		pthread_mutex_unlock(data->philos[p_num].last_eating_mut);
		return ;
	}
	pthread_mutex_unlock(data->philos[p_num].state_mut);
	pthread_mutex_unlock(data->philos[p_num].last_eating_mut);
}

void	ft_right_first_fork_lock(t_data *data, int p_num)
{
	while (1)
	{
		pthread_mutex_lock(data->philos[p_num].right_sfgrd);
		if (!*data->philos[p_num].right_fork)
			*data->philos[p_num].right_fork = 1;
		pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
		pthread_mutex_lock(data->philos[p_num].left_sfgrd);
		if (!*data->philos[p_num].left_fork)
		{
			*data->philos[p_num].left_fork = 1;
			pthread_mutex_lock(&data->print);
			printf("%lu %i has taken a fork\n", (ft_get_time() - data->start_time), p_num);
			pthread_mutex_unlock(&data->print);
			pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
			break ;
		}
		else
			*data->philos[p_num].right_fork = 0;
		pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
		ft_usleep(data->eat / 12);
	}
}

void	ft_left_first_fork_lock(t_data *data, int p_num)
{
	while (1)
	{
		// pthread_mutex_lock(&data->print);
		// printf("while get fork l from philo %i @ %li\n", p_num, (data->start_time - get_time()));
		// pthread_mutex_unlock(&data->print);
		pthread_mutex_lock(data->philos[p_num].left_sfgrd);
		if (!*data->philos[p_num].left_fork)
			*data->philos[p_num].left_fork = 1;
		pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
		pthread_mutex_lock(data->philos[p_num].right_sfgrd);
		if (!*data->philos[p_num].right_fork)
		{
			*data->philos[p_num].right_fork = 1;
			pthread_mutex_lock(&data->print);
			printf("%lu %i has taken a fork\n", (ft_get_time() - data->start_time), p_num);
			pthread_mutex_unlock(&data->print);
			pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
			break ;
		}
		else
			*data->philos[p_num].left_fork = 0;
		pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
		ft_usleep(data->eat / 8);
	}
}
