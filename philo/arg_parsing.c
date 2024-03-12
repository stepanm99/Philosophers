/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:59:14 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/11 18:10:29 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief In case of one philosopher, which will die at time to die
/// @param data Main data struct
void	ft_single_philo(t_data *data)
{
	ft_usleep(data->die);
	printf("%i 1 died\n", data->die);
	ft_free_data(data, 2);
	exit(0);
}

/// @brief Checks if the argument is number only
/// @param str String of the input argument
/// @return 1 if wrong, 0 if ok
char	ft_check_string(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

/// @brief Converts string to integer
/// @param str Input string to be converted
/// @param data Main data struct (used in case of error)
/// @return Integer converted from string
int	ft_atoi(const char *str, t_data *data)
{
	size_t	i;
	int		negflag;
	int		n;

	i = 0;
	n = 0;
	negflag = 1;
	if (ft_check_string(str))
		ft_error(data, ARGUMENT_ERR);
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
	if (argc == 5 || argc == 6)
	{
		data->num_of_philos = ft_atoi(argv[1], data);
		data->die = ft_atoi(argv[2], data);
		data->eat = ft_atoi(argv[3], data);
		data->sleep = ft_atoi(argv[4], data);
		if (argc == 6)
			data->must_eat = ft_atoi(argv[5], data);
		else
			data->must_eat = 0;
	}
	else
		ft_error(data, ARGUMENT_ERR);
	if (data->num_of_philos == 1)
		ft_single_philo(data);
}
