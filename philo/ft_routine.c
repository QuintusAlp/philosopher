/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:03:59 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/11 15:34:02 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

int	ft_philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	else
		return (pthread_mutex_unlock(philo->dead_mutex), 0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!ft_philo_is_dead(philo))
	{
		ft_eat(philo);
		if (philo->nbr_meals >= philo->nbr_each_philo_must_eat)
			break ;
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_start_routines(pthread_t *threads, t_philo *philo)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (!((i + 1) % 2))
			ft_usleep(5);
		if (pthread_create(&threads[i], NULL, routine, &philo[i]))
			return (ft_error("failed to create thread\n"), 1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, ft_monitoring, philo))
		return (ft_error("failed to create thread\n"), 1);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (ft_error("failed to join thread\n"), 1);
		i++;
	}
	if (pthread_join(monitor_thread, NULL))
		return (ft_error("failed to join thread\n"), 1);
	return (0);
}
