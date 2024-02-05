#include "philosophers.h"

char	ft_check_state(t_data *data, int p_num)
{
	pthread_mutex_lock(data->philos[p_num].state_mut);
	if (data->philos[p_num].state)
	{
		pthread_mutex_unlock(data->philos[p_num].state_mut);
		return (0);
	}
	pthread_mutex_unlock(data->philos[p_num].state_mut);
	return (1);
}

void	ft_forks_unlock(t_data *data, int p_num)
{
	pthread_mutex_lock(data->philos[p_num].left_sfgrd);
	*data->philos[p_num].left_fork = 0;
	pthread_mutex_unlock(data->philos[p_num].left_sfgrd);
	pthread_mutex_lock(data->philos[p_num].right_sfgrd);
	*data->philos[p_num].right_fork = 0;
	pthread_mutex_unlock(data->philos[p_num].right_sfgrd);
}

void	ft_print_eat(t_data *data, int p_num)
{
	pthread_mutex_unlock(data->philos[p_num].state_mut);
	pthread_mutex_lock(&data->print);
	printf("%lu %i is eating\n", (ft_get_time() - data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
	ft_usleep(data->eat);
	pthread_mutex_lock(data->philos[p_num].ate_mut);
	data->philos[p_num].ate++;
	pthread_mutex_unlock(data->philos[p_num].ate_mut);
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
	ft_print_eat(data, p_num);
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

void	ft_print_take_fork(t_data *data, int p_num)
{
	pthread_mutex_lock(&data->print);
	printf("%lu %i has taken a fork\n", (ft_get_time()
			- data->start_time), p_num);
	pthread_mutex_unlock(&data->print);
}
