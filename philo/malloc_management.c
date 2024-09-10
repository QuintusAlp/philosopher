/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:33:39 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/10 20:33:55 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

int	ft_malloc_all(t_data *data)
{	
	data->philosophers = NULL;
	data->threads= NULL;
	data->forks= NULL;
	data->dead_mutex= NULL;
	data->eat_mutex= NULL;
	data->philosophers = malloc(data->nbr_philo * sizeof(t_philo));
	if (!data->philosophers)
		return (ft_error("malloc erro\n"));
	data->threads = malloc(data->nbr_philo* sizeof(pthread_t));
	if (!data->threads)
		return (ft_error("malloc error\n"));
	data->forks = malloc(data->nbr_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ft_error("malloc erro\n"));
	data->dead_mutex = malloc(data->nbr_philo * sizeof(pthread_mutex_t));
	if (!data->dead_mutex)
		return (ft_error("malloc erro\n"));
	data->eat_mutex = malloc (data->nbr_philo * sizeof(pthread_mutex_t));
	if (!data->eat_mutex)
		return (ft_error("malloc erro\n"));
	return (0);

}
void	ft_free_all(t_data *data)
{
	if (data->philosophers != NULL)
		free(data->philosophers);
	if (data->threads != NULL)
		free(data->threads);
	if (data->forks != NULL)
		free(data->forks);
	if (data->dead_mutex != NULL)
		free(data->dead_mutex);
	if (data->eat_mutex != NULL)
		free(data->eat_mutex);
	
}