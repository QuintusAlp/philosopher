/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:47:53 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/04 12:34:54 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void *routine(void *args)
{
	t_philo *philo = (t_philo *)args;
	
	pthread_mutex_lock(philo->dead_mutex);
	while (!philo->dead)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		ft_print_mutex(FORK,philo);
		ft_print_mutex(FORK,philo);
		ft_print_mutex(EAT,philo);
		if (!philo->dead)
			ft_usleep(philo->time_to_eat);
		philo->number_of_meals += 1;
		philo->last_eating_time = get_current_time() - philo->init_timestamp;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		ft_print_mutex(SLEEP,philo);
		if (!philo->dead)
			ft_usleep(philo->time_to_sleep);
		ft_print_mutex(THINK,philo);
	}
	pthread_mutex_unlock(philo->dead_mutex);
	return (NULL);
}

void	ft_start_routines(pthread_t *threads, t_philo *philosophers, t_data data)
{
	int	i;
	pthread_t monitor_thread;

	pthread_create(&monitor_thread, NULL, ft_monitoring, philosophers);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_create(&threads[i], NULL,routine, &philosophers[i]);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}