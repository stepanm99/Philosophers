/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:11 by smelicha          #+#    #+#             */
/*   Updated: 2024/03/02 19:47:09 by smelicha         ###   ########.fr       */
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

# define ALLOCATION_ERR 1
# define ARGUMENT_ERR 2
# define THREAD_ERR 3
# define MUTEX_ERR 4

# ifndef PRINT_NUMBER_OF_EATS
#  define PRINT_NUMBER_OF_EATS 0
# endif

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
	char			waiter_flag;
	char			*right_fork;
	char			*left_fork;
}	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	int				eat;
	int				sleep;
	int				die;
	int				must_eat;
	uint64_t		start_time;
	uint64_t		delayed_start;
	pthread_t		grim_reaper;
	char			*overeaters;
	pthread_mutex_t	print;
	pthread_mutex_t	*philo_data_mutex;
	pthread_mutex_t	*fork_mutex;
	char			*forks;
	t_philo			*philos;
}	t_data;

typedef struct s_philo_arg
{
	t_data	*data;
	t_philo	*philo;
	int		p_num;
}	t_philo_arg;

/*Utilities*/
int			ft_atoi(const char *str, t_data *data);

/*Time*/
uint64_t	ft_get_time(void);
void		ft_usleep(uint64_t delay);
void		ft_synchro_start(t_data *data, char w_flag);

/*Data handling*/
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
void		deploy_eaters(t_data *data);
void		deploy_rest(t_data *data);
void		ft_odd_deploy_loop(t_data *data, t_philo_arg arg, int i,
				char w_flag);
void		ft_even_deploy_loop(t_data *data, t_philo_arg arg, int i,
				char w_flag);
void		ft_wait_for_thread(t_data *data, int p_num);

/*Philosopher functions*/
void		*ft_philosopher(void *arg_ptr);
char		ft_eat(t_data *data, int p_num);
void		ft_sleep(t_data *data, int p_num);
void		ft_think(t_data *data, int p_num);
void		ft_forks_unlock(t_data *data, int p_num);
void		ft_eat_dealy_and_stat_update(t_data *data, int p_num);
void		ft_right_first_fork_lock(t_data *data, int p_num);
void		ft_left_first_fork_lock(t_data *data, int p_num);
char		ft_death_check(t_data *data, int p_num);
char		ft_check_state(t_data *data, int p_num);
void		ft_print_take_fork(t_data *data, int p_num);
void		ft_print_eat_and_delay(t_data *data, int p_num);

/*Grim reaper thread function*/
void		*ft_grim_reaper(t_data *data);
void		ft_funeral(t_data *data, int carcass_nr, char print);
char		obesity_alert(t_data *data, int fatty_nr);
void		ft_print_philos_stomachs(t_data *data);

#endif
