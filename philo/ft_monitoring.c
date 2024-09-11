/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 07:42:58 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/11 15:18:58 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

int	ft_nbr_full_philo(t_philo *philo)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_lock(philo[i].eat_mutex);
		if (philo[i].nbr_meals == philo->nbr_each_philo_must_eat)
			nbr++;
		pthread_mutex_unlock(philo[i].eat_mutex);
		i++;
	}
	return (nbr);
}

int	ft_check_death(t_philo *philo)
{
	size_t	laps_time;
	size_t	relative_time;

	pthread_mutex_lock(philo->eat_mutex);
	relative_time = (ft_current_time() - philo->init_timestamp);
	laps_time = relative_time - philo->last_eating_time;
	if (laps_time >= philo->time_to_die)
		return (pthread_mutex_unlock(philo->eat_mutex), 1);
	else
		return (pthread_mutex_unlock(philo->eat_mutex), 0);
}

void	ft_kill_all_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_lock(philo[i].dead_mutex);
		philo[i].dead = 1;
		pthread_mutex_unlock(philo[i].dead_mutex);
		i++;
	}
}

void	*ft_monitoring(void *arg)
{
	t_philo	*philo;
	int		i;
	int		end;

	end = 1;
	philo = (t_philo *)arg;
	while (end)
	{
		i = 0;
		while (i < philo->number_of_philosophers)
		{
			if (ft_check_death(&philo[i]))
			{
				ft_print_mutex(DEAD, &philo[i]);
				ft_kill_all_philo(philo);
				end = 0;
				break ;
			}
			i++;
		}
		if (ft_nbr_full_philo(philo) >= philo->number_of_philosophers)
			end = 0;
	}
	return (NULL);
}
