/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:50:09 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/08 12:36:25 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
void	ft_destroy(pthread_mutex_t *forks, int j)
{
	int	i;

	i = 0;
	while(i < j)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
int	ft_init_mutex(pthread_mutex_t *mutex, t_data *data)
{
	int	i;

	i = 0;
	while(i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
			return (ft_destroy(mutex, i), 1);
		i++;
	}
	if (pthread_mutex_init(&data->dead_mutex, NULL))
		return(ft_destroy(mutex, i), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return(ft_destroy(mutex, i),pthread_mutex_destroy(&data->dead_mutex), 1);
	return (0);
}

void	ft_init_philosophers(t_philo *philosophers, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philosophers[i].index = i;
		philosophers[i].dead = 0;
		philosophers[i].init_timestamp = data->init_timestamp;
		philosophers[i].time_to_eat = data->time_to_eat;
		philosophers[i].time_to_sleep = data->time_to_sleep;
		philosophers[i].time_to_die = data->time_to_die;
		philosophers[i].number_of_philosophers= data->number_of_philosophers;
		philosophers[i].number_of_times_each_philosopher_must_eat = data->number_of_times_each_philosopher_must_eat;
		philosophers[i].number_of_meals = 0;
		philosophers[i].l_fork = &forks[i];
		philosophers[i].r_fork = &forks[(i + 1) % data->number_of_philosophers];
		philosophers[i].last_eating_time = ft_current_time() - data->init_timestamp;
		philosophers[i].print_mutex = &data->print_mutex;
		philosophers[i].dead_mutex = &data->dead_mutex;
		philosophers[i].is_eating = 0;
		i++;
	}
}

