/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deployment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:51:38 by smelicha          #+#    #+#             */
/*   Updated: 2024/02/09 22:48:22 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Function waits until the thread works, signalled by state != 2
/// @param data Main data struct
/// @param p_num Number of philosopher to wait for
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
