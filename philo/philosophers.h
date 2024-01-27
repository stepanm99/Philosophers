/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:11 by smelicha          #+#    #+#             */
/*   Updated: 2024/01/16 22:44:12 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

/*Defining OS dependent mutex variable names*/

# ifdef __APPLE__
#  define MUTEX_NUM __sig
# endif
# ifdef __linux__
#  define MUTEX_NUM __data.__lock
# endif

# define ALLOCATION_ERR 1
# define ARGUMENT_ERR 2
# define THREAD_ERR 3
# define MUTEX_ERR 4

/*state:
	0 - dead
	1 - alive
	2 - eating/starting
*/
typedef struct s_philo
{
	pthread_t		thread_id;
	int				number;
	int				ate;
	uint64_t		last_eating;
	char			state;
	pthread_mutex_t	*state_mut;
	pthread_mutex_t	*last_eating_mut;
	pthread_mutex_t	*ate_mut;
	char			*right_fork;
	pthread_mutex_t	*right_sfgrd;
	char			*left_fork;
	pthread_mutex_t	*left_sfgrd;
}	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	int				eat;
	int				sleep;
	int				die;
	int				must_eat;
	char			print_flag;
	uint64_t		start_time;
	pthread_t		grim_reaper;
	char			*overeaters;
	pthread_mutex_t	print;
	char			*forks;
	t_philo			*philos;
	pthread_mutex_t	*fork_safeguard;
	pthread_mutex_t	*state_mut;
	pthread_mutex_t	*last_eating_mut;
	pthread_mutex_t	*ate_mut;
}	t_data;

typedef struct s_philo_arg
{
	t_data	*data;
	int		p_num;
}	t_philo_arg;

/*Utilities*/
int			ft_atoi(const char *str, t_data *data);

/*Time*/
uint64_t	get_time(void);
void		ft_usleep(uint64_t delay);
void		ft_synchro_start(t_data *data);

/*Data handling*/
void		arg_pars(t_data *data, int argc, const char **argv);
void		free_data(t_data *data);
void		prepare_philos_data(t_data *data);
void		prepare_forks_data(t_data *data);

/*Error*/
void		error(t_data *data, int errno);

/*Philosopher thread deploying*/
void		deploy_philosophers(t_data *data);

/*Philosopher functions*/
void		philosopher(void *arg_ptr);
void		ft_eat(t_data *data, int p_num);
void		ft_sleep(t_data *data, int p_num);
void		ft_think(t_data *data, int p_num);
void		ft_forks_unlock(t_data *data, int p_num);
void		ft_sleep_and_stat_update(t_data *data, int p_num);
void		ft_right_first_fork_lock(t_data *data, int p_num);
void		ft_left_first_fork_lock(t_data *data, int p_num);
void		ft_death_check(t_data *data, int p_num);


/*Grim reaper thread function*/
void		grim_reaper(t_data *data);

/*Debug*/
void		print_data(t_data *data);
void		time_test(int time);
void		print_philos(t_data *data);

#endif
