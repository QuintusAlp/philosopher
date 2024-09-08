/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:03:59 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/06 14:16:57by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

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
	t_philo	*philo = (t_philo *) arg;
	while (!ft_philo_is_dead(philo))
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		if (!philo->dead)
		{
			ft_print_mutex(FORK, philo);
			ft_print_mutex(FORK, philo);
			ft_print_mutex(EAT, philo);
		}
		if (!philo->dead)
		{
			philo->is_eating = 1;
			ft_usleep(philo->time_to_eat);
			philo->last_eating_time = ft_current_time() - philo->init_timestamp;
			philo->number_of_meals += 1;
			philo->is_eating = 0;
		}
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		if (philo->number_of_meals == philo->number_of_times_each_philosopher_must_eat)
			break ;
		ft_print_mutex(SLEEP, philo);
		if (!philo->dead)
			ft_usleep(philo->time_to_sleep);
		ft_print_mutex(THINK, philo);
	}
	return (NULL);
}
int	ft_nbr_full_philo(t_philo *philo)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (i < philo->number_of_philosophers)
	{
		if (philo[i].number_of_meals == philo->number_of_times_each_philosopher_must_eat)
			nbr++;
		i++;
	}
	return (nbr);
}
int	ft_check_death(t_philo *philo)
{
	if ((ft_current_time() - philo->init_timestamp) - philo->last_eating_time >= philo->time_to_die && !philo->is_eating)
		return (1);
	else
		return (0);
}
void	ft_kill_all_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		philo[i].dead = 1;
		i++;
	}
}
void	*ft_monitoring(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int	i;
	int	nbr_philo;
	int	end;
	
	end  = 1;
	nbr_philo = philo->number_of_philosophers;
	while (end)
	{
		i = 0;
		while (i < nbr_philo)
		{
			if (ft_check_death(&philo[i]))
			{
				pthread_mutex_lock(philo->dead_mutex);
				ft_print_mutex(DEAD, &philo[i]);
				ft_kill_all_philo(philo);
				end = 0;
				pthread_mutex_unlock(philo->dead_mutex);
				break ;
			}
			i++;
		}
		if (ft_nbr_full_philo(philo) >= philo->number_of_philosophers)
			end = 0;
	}
	return (NULL);
}
int	ft_start_routines(pthread_t *threads, t_philo *philo)
{
	int	i;
	pthread_t monitor_thread;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, routine, &philo[i]))
        		return (ft_error("failed to create thread\n"), 1);
		i++;
	}
	pthread_create(&monitor_thread, NULL, ft_monitoring, philo);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

//ROUTINE
// int i = 0;
	// while (!philo->dead && i < 5)
	// {
	// 	pthread_mutex_lock(philo->l_fork);
	// 	pthread_mutex_lock(philo->r_fork);
	// 	pthread_mutex_lock(philo->dead_mutex);
	// 	// if (!philo->dead)
	// 	// {
	// 	// 	ft_print_mutex(FORK, philo);
	// 	// 	ft_print_mutex(FORK, philo);
	// 	// 	ft_print_mutex(EAT, philo);
	// 	// }
	// 	if (!philo->dead)
	// 		ft_usleep(philo->time_to_eat);
	// 	philo->last_eating_time = ft_current_time() - philo->init_timestamp;
	// 	// philo->number_of_meals += 1;
	// 	// ft_usleep(philo->time_to_eat);
	// 	pthread_mutex_unlock(philo->dead_mutex);
	// 	pthread_mutex_unlock(philo->l_fork);
	// 	pthread_mutex_unlock(philo->r_fork);
	// 	//if (philo->number_of_meals == philo->number_of_times_each_philosopher_must_eat)
	// 	//	break ;
	// 	// ft_print_mutex(SLEEP, philo);
	// 	// if (!philo->dead)
	// 	// 	ft_usleep(philo->time_to_sleep);
	// 	// ft_print_mutex(THINK, philo);
	// 	i++;
	// }

	//MONITORING
	// printf("philo %d %lu - %lu >= %lu ?\n", i, (ft_current_time() - philo->init_timestamp), philo[i].last_eating_time, philo[i].time_to_die);
			// if ((ft_current_time() - philo->init_timestamp) - philo[i].last_eating_time >= philo[i].time_to_die)
			// 	printf("%d is dead\n", i);
			// {
				// printf(" %d DEAD\n", i);
			// 	ft_print_mutex(DEAD, philo);
			// 	end = 0;
			// 	i = 0;
			// 	while (i < philo->number_of_philosophers)
			// 	{
			// 		philo[i].dead = 1;
			// 		i++;
			// 	}
			// 	pthread_mutex_unlock(philo[i].dead_mutex);
			// 	break ;
			// }
			// else