/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 07:42:58 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/09 08:48:12 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_nbr_full_philo(t_philo *philo)
{
	int	i;
	int	nbr_philo_must_e;
	int	nbr;

	i = 0;
	nbr = 0;
	nbr_philo_must_e = philo->number_of_times_each_philosopher_must_eat;
	while (i < philo->number_of_philosophers)
	{
		if (philo[i].number_of_meals == nbr_philo_must_e)
			nbr++;
		i++;
	}
	return (nbr);
}

int	ft_check_death(t_philo *philo)
{
	size_t	laps_time;
	size_t	i;

	i = (ft_current_time() - philo->init_timestamp);
	laps_time = i - philo->last_eating_time;
	if (laps_time >= philo->time_to_die && !philo->is_eating)
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
