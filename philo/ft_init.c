/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:50:09 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/11 15:27:57 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

int	ft_init_mutex(t_data *data)
{
	if (ft_init_malloc_mutex(data->forks, data))
		return (1);
	if (ft_init_malloc_mutex(data->dead_mutex, data))
		return (ft_destroy(data->forks, data->nbr_philo), 1);
	if (ft_init_malloc_mutex(data->eat_mutex, data))
		return (ft_destroy(data->forks, data->nbr_philo),
			ft_destroy(data->dead_mutex, data->nbr_philo), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		ft_destroy(data->forks, data->nbr_philo);
		ft_destroy(data->dead_mutex, data->nbr_philo);
		ft_destroy(data->eat_mutex, data->nbr_philo);
		return (1);
	}
	return (0);
}

void	philo_add(t_philo *philosophers, t_data *data, int i, int ntpm)
{
	size_t	current_time;

	current_time = ft_current_time() - data->init_timestamp;
	philosophers[i].index = i;
	philosophers[i].dead = 0;
	philosophers[i].init_timestamp = data->init_timestamp;
	philosophers[i].time_to_eat = data->time_to_eat;
	philosophers[i].time_to_sleep = data->time_to_sleep;
	philosophers[i].time_to_die = data->time_to_die;
	philosophers[i].number_of_philosophers = data->nbr_philo;
	philosophers[i].nbr_each_philo_must_eat = ntpm;
	philosophers[i].nbr_meals = 0;
	philosophers[i].l_fork = &data->forks[i];
	philosophers[i].r_fork = &data->forks[(i + 1) % data->nbr_philo];
	philosophers[i].last_eating_time = current_time;
	philosophers[i].print_mutex = &data->print_mutex;
	philosophers[i].dead_mutex = &data->dead_mutex[i];
	philosophers[i].eat_mutex = &data->eat_mutex[i];
}

void	ft_init_philosophers(t_philo *philosophers, t_data *data)
{
	int		i;
	int		ntpm;

	i = -1;
	ntpm = data->nbr_each_philo_must_eat;
	while (i++, i < data->nbr_philo)
	{
		philo_add(philosophers, data, i, ntpm);
	}
}
