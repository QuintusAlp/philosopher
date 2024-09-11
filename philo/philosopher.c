/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:29:57 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/11 15:30:24 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

int	ft_parsing(int argc, char **argv, t_data *data)
{
	if (argc != 6 && argc != 5)
		return (ft_error("wrong number of args\n"), 1);
	data->nbr_philo = ft_atoi(argv[1]);
	if (data->nbr_philo < 1)
		return (ft_error("wrong number of philosophers\n"), 1);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die < 1)
		return (ft_error("wrong time to die\n"), 1);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat < 1)
		return (ft_error("wrong time to eat\n"), 1);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep < 1)
		return (ft_error("wrong time to sleep\n"), 1);
	if (argc == 5)
		data->nbr_each_philo_must_eat = -1;
	else
	{
		data->nbr_each_philo_must_eat = ft_atoi(argv[5]);
		if (data->nbr_each_philo_must_eat < 1)
			return (ft_error("wrong number each philosopher must eat\n"), 1);
	}
	data->init_timestamp = ft_current_time();
	return (0);
}

void	ft_destroy_all(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->eat_mutex[i]);
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->dead_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(philo->dead_mutex);
	pthread_mutex_destroy(philo->print_mutex);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (ft_parsing(argc, argv, &data))
		return (1);
	if (data.nbr_philo == 1)
		return (ft_one_philo(&data), 0);
	if (ft_malloc_all(&data))
		return (ft_free_all(&data), 1);
	if (ft_init_mutex(&data))
		return (ft_free_all(&data), ft_error("mutex init issue"));
	ft_init_philosophers(data.philosophers, &data);
	if (ft_start_routines(data.threads, data.philosophers))
	{
		ft_free_all(&data);
		ft_destroy_all(&data, data.philosophers);
		return (1);
	}
	ft_free_all(&data);
	ft_destroy_all(&data, data.philosophers);
	return (0);
}
