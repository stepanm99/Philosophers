/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:18 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/17 23:21:19 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, const char **argv)
{
	t_data	*data;
	int		i;

	i = 10;
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		error(data, 1);
	arg_pars(data, argc, argv);
	print_data(data);
	pthread_mutex_init(&data->print, NULL); //initialize print mutex
	prepare_forks_data(data);
	prepare_philos_data(data);
	print_philos(data);
	data->start_time = get_time();
	print_data(data);
	free_data(data);
	system("leaks philo");
	return (0);
}
