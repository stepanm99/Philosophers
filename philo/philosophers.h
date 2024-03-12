/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:11 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/11 18:57:51 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define ALLOCATION_ERR 1
# define ARGUMENT_ERR 2
# define THREAD_ERR 3
# define MUTEX_ERR 4

# ifndef PRINT_NUMBER_OF_EATS
#  define PRINT_NUMBER_OF_EATS 0
# endif

/*Philosopher data struct
	state:
	0 - dead
	1 - alive
	2 - eating/starting
*/
typedef struct s_philo
{
	pthread_t		thread_id;
	int				number;
	int				ate;
	int				eat;
	int				sleep;
	int				die;
	uint64_t		last_eating;
	uint64_t		*start_time;
	char			state;
	char			*right_fork;
	char			*left_fork;
	pthread_mutex_t	*left_sfgrd;
	pthread_mutex_t	*right_sfgrd;
	pthread_mutex_t	*print;
	pthread_mutex_t	*data_mut;
}	t_philo;

/*Main data struct*/
typedef struct s_data
{
	int				num_of_philos;
	int				eat;
	int				sleep;
	int				die;
	int				must_eat;
	uint64_t		start_time;
	pthread_t		grim_reaper;
	char			*overeaters;
	pthread_mutex_t	print;
	pthread_mutex_t	*philo_data_mutex;
	pthread_mutex_t	*fork_mutex;
	char			*forks;
	t_philo			*philos;
}	t_data;

/*Struct for argument given to philo thread function*/
typedef struct s_philo_arg
{
	t_data	*data;
	t_philo	*philo;
	int		p_num;
}	t_philo_arg;

/*Utilities*/
int			ft_atoi(const char *str, t_data *data);

/*Time functions*/
uint64_t	ft_get_time(void);
uint64_t	ft_get_utime(void);
void		ft_usleep(uint64_t delay);
void		ft_synchro_start(uint64_t start_time);
void		ft_wait_for_start_time(uint64_t *start_time, pthread_mutex_t *lock);

/*Data handling*/
void		ft_data_init(t_data *data);
void		ft_arg_pars(t_data *data, int argc, const char **argv);
void		ft_free_data(t_data *data, int errno);
void		ft_destroy_mutexes(t_data *data);
void		ft_prepare_philos_data(t_data *data);
void		ft_prepare_forks_data(t_data *data);

/*Error*/
void		ft_error(t_data *data, int errno);
void		ft_single_philo(t_data *data);

/*Philosopher thread deploying*/
void		ft_deploy_philosophers(t_data *data);
void		ft_wait_for_thread(t_data *data, int p_num);

/*Philosopher thread functions*/
void		*ft_philosopher(void *arg_ptr);
char		ft_eat(t_philo *philo, int p_num);
void		ft_sleep(t_philo *philo, int p_num);
void		ft_think(t_philo *philo, int p_num);
void		ft_forks_release_left_first(t_philo *philo);
void		ft_forks_release_right_first(t_philo *philo);
void		ft_eat_delay_and_stat_update(t_philo *philo, int p_num);
void		ft_right_first_fork_lock(t_philo *philo, int p_num);
void		ft_left_first_fork_lock(t_philo *philo, int p_num);
char		ft_death_check(t_philo *philo);
void		ft_print_take_fork(t_philo *philo, int p_num);
void		ft_print_eat_and_delay(t_philo *philo, int p_num);

/*Grim reaper thread function*/
void		*ft_grim_reaper(t_data *data);
void		ft_funeral(t_data *data, int carcass_nr, char print);
char		obesity_alert(t_data *data, int fatty_nr);
void		ft_print_philos_stomachs(t_data *data);

#endif
