/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:50:09 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/09 15:58:10 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

int	ft_malloc(t_data *data)
{
	data->forks = malloc(data->number_of_philosophers
			* sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ft_error("malloc erro\n"), 1);
	data->dead_mutex = malloc(data->number_of_philosophers
			* sizeof(pthread_mutex_t));
	if (!data->dead_mutex)
		return (ft_error("malloc erro\n"), free(data->forks), 1);
	data->eat_mutex = malloc (data->number_of_philosophers
			* sizeof(pthread_mutex_t));
	if (!data->eat_mutex)
		return (ft_error("malloc erro\n"), free(data->forks),
			free(data->dead_mutex), 1);
	return (0);
}

int	ft_init_mutex(t_data *data)
{
	if (ft_malloc(data))
		return (1);
	if (ft_init_malloc_mutex(data->forks, data))
		return (free(data->forks),
			free(data->dead_mutex), free(data->eat_mutex), 1);
	if (ft_init_malloc_mutex(data->dead_mutex, data))
		return (ft_destroy(data->forks,
				data->number_of_philosophers), free(data->dead_mutex),
			free(data->eat_mutex), 1);
	if (ft_init_malloc_mutex(data->eat_mutex, data))
		return (ft_destroy(data->forks, data->number_of_philosophers),
			ft_destroy(data->dead_mutex, data->number_of_philosophers),
			free(data->forks),
			free(data->dead_mutex), free(data->eat_mutex), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		ft_destroy(data->forks, data->number_of_philosophers);
		ft_destroy(data->dead_mutex, data->number_of_philosophers);
		ft_destroy(data->eat_mutex, data->number_of_philosophers);
		return (free(data->forks),
			free(data->dead_mutex), free(data->eat_mutex), 1);
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
	philosophers[i].number_of_philosophers = data->number_of_philosophers;
	philosophers[i].number_of_times_each_philosopher_must_eat = ntpm;
	philosophers[i].number_of_meals = 0;
	philosophers[i].l_fork = &data->forks[i];
	philosophers[i].r_fork
		= &data->forks[(i + 1) % data->number_of_philosophers];
	philosophers[i].last_eating_time = current_time;
	philosophers[i].print_mutex = &data->print_mutex;
	philosophers[i].dead_mutex = &data->dead_mutex[i];
	philosophers[i].eat_mutex = &data->eat_mutex[i];
	philosophers[i].is_eating = 0;
}

void	ft_init_philosophers(t_philo *philosophers, t_data *data)
{
	int		i;
	int		ntpm;

	i = -1;
	ntpm = data->number_of_times_each_philosopher_must_eat;
	while (i++, i < data->number_of_philosophers)
	{
		philo_add(philosophers, data, i, ntpm);
	}
}
