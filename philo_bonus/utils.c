/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:04:58 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/27 15:05:08 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

unsigned long	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

unsigned long	get_passed_time(unsigned long begin)
{
	return (get_current_time() - begin);
}

void	print_message(t_philo *philo, char *message)
{
	sem_wait(philo->data->print);
	if (philo->data->is_dead != 0)
	{
		sem_post(philo->data->print);
		return ;
	}
	printf("%lu %d %s\n", get_passed_time(philo->data->start_time), philo->id,
		message);
	sem_post(philo->data->print);
}

void	smart_sleep(int time, t_data *data)
{
	unsigned long	begin;

	begin = get_current_time();
	while (get_passed_time(begin) <= (unsigned long)time && data->is_dead == 0)
		usleep(100);
}
