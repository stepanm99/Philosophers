/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:11 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/15 17:59:14 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>



typedef struct s_data
{
	int	num_of_philos;
	int	eat;
	int	sleep;
	int	die;
	int	must_eat;
}	t_data;


/*Utilities*/
int		ft_atoi(const char *str, t_data *data);

/*Data handling*/
void	arg_pars(t_data *data, int argc, const char **argv);
void	free_data(t_data *data);

/*Error*/
void	error(t_data *data, int errno);

/*Debug*/
void	print_data(t_data *data);