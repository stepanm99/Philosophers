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
//	int		i;

//	i = 0;
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		error(data, 1);
	arg_pars(data, argc, argv);
//	printf("num of philos from main: %i\n", data->num_of_philos);
//	data->start = 0;
	data->print_flag = 1;
	data->must_eat = 0;
	print_data(data);
	pthread_mutex_init(&data->print, NULL); //initialize print mutex
	prepare_forks_data(data);
	// while (i != data->num_of_philos)
	// {
	// 	printf("fork[%i] = %i\n", i, data->forks[i].MUTEX_NUM);
	// 	i++;
	// }
	prepare_philos_data(data);
//	print_philos(data);
	data->start_time = get_time() - ((data->num_of_philos * 10));
	deploy_philosophers(data);
//	print_data(data);
	free_data(data);
//	system("leaks philo");
	return (0);
}
