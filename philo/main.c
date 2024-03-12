/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:18 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/11 18:31:09 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, const char **argv)
{
	t_data	*data;
	int		i;

	i = 0;
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(data, ALLOCATION_ERR);
	ft_data_init(data);
	ft_arg_pars(data, argc, argv);
	pthread_mutex_init(&data->print, NULL);
	data->start_time = 0;
	ft_prepare_forks_data(data);
	ft_prepare_philos_data(data);
	ft_deploy_philosophers(data);
	while (i != data->num_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	ft_free_data(data, 0);
	return (0);
}
