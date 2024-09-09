/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:29:57 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/09 17:24:13 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

int	ft_parsing(int argc, char **argv, t_data *data)
{
	if (argc != 6 && argc != 5)
		return (ft_error("wrong number of args\n"), 1);
	data->number_of_philosophers = ft_atoi(argv[1]);
	if (data->number_of_philosophers < 2)
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
		data->number_of_times_each_philosopher_must_eat = -1;
	else
	{
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (data->number_of_times_each_philosopher_must_eat < 1)
			return (ft_error("wrong number each philosopher must eat\n"), 1);
	}
	data->init_timestamp = ft_current_time();
	return (0);
}

void	ft_destroy_all(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
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
	t_philo			*philosophers;
	pthread_t		*threads;

	if (ft_parsing(argc, argv, &data))
		return (1);
	philosophers = malloc(data.number_of_philosophers * sizeof(t_philo));
	if (!philosophers)
		return (ft_error("malloc erro\n"), 1);
	threads = malloc(data.number_of_philosophers * sizeof(pthread_t));
	if (!threads)
		return (free(philosophers), ft_error("malloc error\n"), 1);
	if (ft_init_mutex(&data))
		return (free(philosophers),
			free(threads),
			ft_error("malloc error\n"), 1);
	ft_init_philosophers(philosophers, &data);
	if (ft_start_routines(threads, philosophers))
		return (1);
	ft_destroy_all(&data, philosophers);
	return (free(philosophers), free(data.forks),
		free(data.dead_mutex), free(data.eat_mutex), free(threads), 0);
}
