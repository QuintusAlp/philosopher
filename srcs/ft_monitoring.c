/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:38:32 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/04 12:35:49 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void *ft_monitoring(void *args)
{
	t_philo	*philosophers = (t_philo *) args;
	int i;
	int end = 1;
	while (end)
	{
		i = 0;
		while (i < philosophers[0].number_of_philosophers)
		{
			if ((get_current_time() - philosophers[i].init_timestamp) - philosophers[i].last_eating_time >= philosophers[i].time_to_die)
			{
				ft_print_mutex(DEAD,&philosophers[i]);
				i = 0;
				end = 0;
				pthread_mutex_lock(philosophers->dead_mutex);
				while(i < philosophers[0].number_of_philosophers)
				{
					philosophers[i].dead = 1;
					i++;
				}
				pthread_mutex_unlock(philosophers->dead_mutex);
			}
			else if (philosophers[i].number_of_meals >= philosophers[i].number_of_times_each_philosopher_must_eat && philosophers[i].number_of_times_each_philosopher_must_eat != -1)
			{
				i = 0;
				end = 0;
				pthread_mutex_lock(philosophers->dead_mutex);
				while(i < philosophers[0].number_of_philosophers)
				{
					philosophers[i].dead = 1;
					i++;
				}
				pthread_mutex_unlock(philosophers->dead_mutex);
			}
			i++;
		}
	}
	return (NULL);
}
