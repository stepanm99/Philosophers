#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>


/*
pthread_create(&data->philos[i].thread_id, NULL, (void *)&ft_philosopher, &arg);
*/

typedef struct s_data{
	pthread_mutex_t	*mut;
	int				id;
}	t_data;

int	thread(void *arg)
{
	int				i;
	t_data			*data;

	data = (t_data *)arg;
	i = 1000000;
	while(i)
	{
		pthread_mutex_lock(data->mut);
//		printf("thd id: %i\t\ti:%i\n", data->id, i);
		i--;
		pthread_mutex_unlock(data->mut);
	}
	return (0);
}

int	main(void)
{
	pthread_mutex_t	mut1;
	pthread_mutex_t	mut2;
	pthread_t		t1;
	pthread_t		t2;
	t_data			*data1 = malloc(sizeof(t_data));
	t_data			*data2 = malloc(sizeof(t_data));

	pthread_mutex_init(&mut1, NULL);
	pthread_mutex_init(&mut2, NULL);
	data1->id = 1;
	data2->id = 2;
	data1->mut = &mut1;
	data2->mut = &mut2;

	pthread_create(&t1, NULL, (void *)&thread, data1);
	pthread_create(&t2, NULL, (void *)&thread, data2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	free(data1);
	free(data2);
	return (0);
}
