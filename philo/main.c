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

// static void	wait_for_tid(t_data *data)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i != data->num_of_philos)
// 	{
// 		if (!data->philos[i].thread_id)
// 			i = 0;
// 		if ((ft_get_time() - data->start_time) > (uint64_t)data->die)
// 		{
// 			pthread_mutex_lock(&data->print);
// 			printf("Too many philos for this computer :(\n");
// 			pthread_mutex_unlock(&data->print);
// 			ft_funeral(data, 0, 0);
// 		}
// 		i++;
// 		ft_usleep(5);
// 	}
// }

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
//	printf("num of philos from main: %i\n", data->num_of_philos);
//	data->start = 0;
	data->print_flag = 1;
	print_data(data);
	pthread_mutex_init(&data->print, NULL); //initialize print mutex
	ft_prepare_forks_data(data);
	// while (i != data->num_of_philos)
	// {
	// 	printf("fork[%i] = %i\n", i, data->forks[i].MUTEX_NUM);
	// 	i++;
	// }
	ft_prepare_philos_data(data);
//	print_philos(data);
	data->start_time = ft_get_time() + ((data->num_of_philos * 100));
	ft_deploy_philosophers(data);
	pthread_mutex_lock(&data->print);
	printf("Main before pthread join loop\n");
	pthread_mutex_unlock(&data->print);
	while (i != data->num_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	pthread_mutex_lock(&data->print);
	printf("Main after pthread join loop\n");
	pthread_mutex_unlock(&data->print);
//	print_data(data);
	ft_print_philos_stomachs(data);
	ft_free_data(data);
//	system("leaks philo");
	return (0);
}
