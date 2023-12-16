/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:18 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/16 20:15:24 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, const char **argv)
{
	t_data	*data;
	int		i;
	
	i = 10;
	printf("argc: %i\n", argc);
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		error(data, 1);
	data->start = malloc(sizeof(struct timeval));
	arg_pars(data, argc, argv);
	print_data(data);
	gettimeofday(data->start, NULL);
	print_start_time(data);
	while (i != 200)
	{
		time_test(i);
		i += 10;
	}
	free_data(data);
	return (0);
}