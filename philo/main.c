#include <stdio.h>
#include "philosophers.h"

int	ft_atoi(const char *str)
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
			return (0);
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

void	arg_pars(t_data *data)
{

}

void	free_data(t_data *data)
{
	if (data)
		free(data);
}

void	error(t_data *data, int errno)
{
	if (data)
		free_data(data);
	if (errno == 2)
		printf("Wrong argument!\n./philo [number of philosophers] [miliseconds to die] [miliseconds to eat] [miliseconds to sleep] [how many times to eat]");
	else if (errno == 1)
		printf("Memory allocation error!\n");
}

int	main(int argc, const char **argv)
{
	t_data	*data;
	
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		error(data, 1);
	arg_pars(data);
	free_data(data);
	return (0);
}