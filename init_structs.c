#include "Philosophers.h"

t_data	*init_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	return (data);
}
t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].last_eat = 0;
		philos[i].is_eating = 0;
		philos[i].data = data;
		i++;
	}
	return (philos);
}

void	init_mutexes(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	i = -1;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&forks[i], 0);
		i++;
	}
	i = -1;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].left_fork = forks[i];
		data->philos[i].right_fork = forks[(i + 1)
			% data->number_of_philosophers];
		i++;
	}
}
