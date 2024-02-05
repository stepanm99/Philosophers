#include "philosophers.h"

void	ft_wait_for_thread(t_data *data, int p_num)
{
	while (1)
	{
		pthread_mutex_lock(&data->state_mut[p_num]);
		if (data->philos[p_num].state != 2)
		{
			pthread_mutex_unlock(&data->state_mut[p_num]);
			break ;
		}
		pthread_mutex_unlock(&data->state_mut[p_num]);
		ft_usleep(50);
	}
}
