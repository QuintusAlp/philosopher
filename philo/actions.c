/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:15:07 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/11 15:27:36 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print_mutex(FORK, philo);
	pthread_mutex_lock(philo->r_fork);
	ft_print_mutex(FORK, philo);
	ft_print_mutex(EAT, philo);
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_eating_time = ft_current_time() - philo->init_timestamp;
	philo->nbr_meals ++;
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_mutex(SLEEP, philo);
	ft_usleep(philo->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print_mutex(THINK, philo);
}
