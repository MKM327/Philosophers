/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:50:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/18 10:39:26 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	check_if_dead(t_philo *philo)
{
	if (get_current_time() - philo->last_eat > philo->data->time_to_die)
		return (1);
	return (0);
}
void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (!philo->data->is_dead)
	{
		eating(philo);
		print_message(philo, "Is sleeping");
		smart_sleep(philo->data->time_to_sleep);
		print_message(philo, "Is thinking");
		if (philo->data->must_eat != -1
			&& philo->eat_count == philo->data->must_eat)
			return (NULL);
		if (check_if_dead(philo))
		{
			print_message(philo, "Is dead");
			philo->data->is_dead = 1;
		}
	}
	return (NULL);
}

void	create_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->number_of_philosophers)
	{
		pthread_create(&(philos[i].thread), NULL, philo, &philos[i]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	data = init_data(argv);
	philos = init_philos(data);
	init_mutexes(data);
	data->start_time = get_current_time();
	create_threads(philos);
	for (int i = 0; i < data->number_of_philosophers; i++)
		pthread_join(philos[i].thread, NULL);
	return (0);
}
