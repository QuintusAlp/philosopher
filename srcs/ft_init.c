/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:42:23 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/04 12:33:14 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_init_philosophers(t_philo *philosophers, t_data data, pthread_mutex_t *forks)
{
	int	i;
	pthread_mutex_t print_mutex;
	pthread_mutex_t dead_mutex;

	i = 0;
	pthread_mutex_init(&print_mutex, NULL);
	while (i < data.number_of_philosophers)
	{
		philosophers[i].index = i;
		philosophers[i].dead = 0;
		philosophers[i].init_timestamp = data.init_timestamp;
		philosophers[i].time_to_eat = data.time_to_eat;
		philosophers[i].time_to_sleep = data.time_to_sleep;
		philosophers[i].time_to_die = data.time_to_die;
		philosophers[i].number_of_philosophers= data.number_of_philosophers;
		philosophers[i].number_of_times_each_philosopher_must_eat = data.number_of_times_each_philosopher_must_eat;
		philosophers[i].number_of_meals = 0;
		philosophers[i].l_fork = &forks[i];
		philosophers[i].r_fork = &forks[(i + 1) % data.number_of_philosophers];
		philosophers[i].last_eating_time = get_current_time() - data.init_timestamp;
		philosophers[i].print_mutex = &print_mutex;
		philosophers[i].dead_mutex = &dead_mutex;
		i++;
	}
}

void	ft_init_forks(pthread_mutex_t *forks, t_data data)
{
	int	i;

	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}