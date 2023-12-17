/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:38:01 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/18 00:39:14 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Here will be the code for thread that periodically checks if
somebody has died*/

void	funeral(t_data *data)
{

}

void	grim_reaper(t_data *data)
{
	int	i;

	i = 0;
	while(1)
	{
		if (!data->philos[i].state)
			funeral(data);
		if (i + 1 != data->num_of_philos)
			i++;
		else
			i = 0;
		usleep(50);
	}
}
