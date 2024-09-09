/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:29:57 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/09 08:21:35 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_parsing(int argc, char **argv, t_data *data)
{
	if (argc != 6 && argc != 5)
		return (ft_error("wrong number of args\n"), 1);
	data->number_of_philosophers = ft_atoi(argv[1]);
	if (data->number_of_philosophers < 1)
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

void	ft_destroy_all(pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
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
	pthread_mutex_t	*forks;

	if (ft_parsing(argc, argv, &data))
		return (1);
	philosophers = malloc(data.number_of_philosophers * sizeof(t_philo));
	if (!philosophers)
		return (ft_error("malloc erro\n"), 1);
	forks = malloc(data.number_of_philosophers * sizeof(pthread_mutex_t));
	if (!forks)
		return (ft_error("malloc erro\n"), 1);
	threads = malloc(data.number_of_philosophers * sizeof(pthread_t));
	if (!threads)
		return (ft_error("malloc erro\n"), 1);
	ft_init_mutex(forks, &data);
	ft_init_philosophers(philosophers, &data, forks);
	if (ft_start_routines(threads, philosophers))
		return (1);
	ft_destroy_all(forks, philosophers);
	return (free(philosophers), free(forks), free(threads), 0);
}
