/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:03:59 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/09 15:58:14 by qalpesse         ###   ########.fr       */
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

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	ft_print_mutex(FORK, philo);
	ft_print_mutex(FORK, philo);
	pthread_mutex_lock(philo->eat_mutex);
	philo->is_eating = 1;
	pthread_mutex_unlock(philo->eat_mutex);
	ft_print_mutex(EAT, philo);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->eat_mutex);
	philo->number_of_meals += 1;
	philo->last_eating_time = ft_current_time() - philo->init_timestamp;
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->eat_mutex);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		ntpme;

	philo = (t_philo *) arg;
	ntpme = philo->number_of_times_each_philosopher_must_eat;
	while (!ft_philo_is_dead(philo))
	{
		ft_eat(philo);
		if (philo->number_of_meals == ntpme)
			break ;
		ft_print_mutex(SLEEP, philo);
		if (!ft_philo_is_dead(philo))
			ft_usleep(philo->time_to_sleep);
		ft_print_mutex(THINK, philo);
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
