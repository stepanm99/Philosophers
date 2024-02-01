/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:18 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/17 20:46:57 by smelicha         ###   ########.fr       */
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
	ft_arg_pars(data, argc, argv);
	data->print_flag = 1;
	pthread_mutex_init(&data->print, NULL);
	ft_prepare_forks_data(data);
	ft_prepare_philos_data(data);
	data->start_time = ft_get_time() + ((data->num_of_philos * 100));
	ft_deploy_philosophers(data);
	while (i != data->num_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	ft_free_data(data);
	return (0);
}
