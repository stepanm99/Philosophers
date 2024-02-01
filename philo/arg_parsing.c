/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:14 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/17 23:13:18 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str, t_data *data)
{
	size_t	i;
	int		negflag;
	int		n;

	i = 0;
	n = 0;
	negflag = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			ft_error(data, 2);
		if (str[i] == '-')
			negflag = (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * negflag);
}

/// @brief Parses arguments to main data struct
/// @param data Main data struct
/// @param argc How many arguments were given
/// @param argv Value of given arguments
void	ft_arg_pars(t_data *data, int argc, const char **argv)
{
	if (argv[1])
		data->num_of_philos = ft_atoi(argv[1], data);
	else
		ft_error(data, 2);
	if (argv[2])
		data->die = ft_atoi(argv[2], data);
	else
		ft_error(data, 2);
	if (argv[3])
		data->eat = ft_atoi(argv[3], data);
	else
		ft_error(data, 2);
	if (argv[4])
		data->sleep = ft_atoi(argv[4], data);
	else
		ft_error(data, 2);
	if (argv[5] && argc == 6)
		data->must_eat = ft_atoi(argv[5], data);
	else
		data->must_eat = 0;
}
