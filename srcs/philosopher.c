/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:29:57 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/04 12:54:02 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_error("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	ft_print_mutex(int flag, t_philo *philo)
{
	if (!philo->dead)
	{
		pthread_mutex_lock(philo->print_mutex);
		if (flag == EAT)
			printf("%zu %d is eating... miam miam\U0001F35D\n",get_current_time() - philo->init_timestamp, philo->index);
		if (flag == FORK)
			printf("%zu %d has taken a fork\U0001F374\n",get_current_time() - philo->init_timestamp, philo->index);
		if (flag == THINK)
			printf("%zu %d is thinking... hmmm\U0001F914\n",get_current_time() - philo->init_timestamp, philo->index);
		if (flag == SLEEP)
			printf("%zu %d is sleeping... zzzzzz\U0001F634\n",get_current_time() - philo->init_timestamp, philo->index);
		if (flag == DEAD)
			printf("\033[31m%zu %d died... miskine\U00002620\033[0m\n",get_current_time() - philo->init_timestamp, philo->index);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

void	ft_parsing(int argc, char **argv, t_data *data)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	if (data->number_of_philosophers < 1)
		ft_error("wrong number of philosopher\n");
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die < 1)
		ft_error("wrong time to die\n");
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat< 1)
		ft_error("wrong time to eat\n");
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep < 1)
		ft_error("wrong time to sleep\n");
	if (argc == 5)
		data->number_of_times_each_philosopher_must_eat = -1;
	else
	{
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (data->number_of_times_each_philosopher_must_eat < 1)
			ft_error("wrong time each philosophers must eat\n");
	}
	data->init_timestamp = get_current_time();
}

void	ft_destroy_mutex(pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(philo->print_mutex);
	pthread_mutex_destroy(philo->dead_mutex);
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
	pthread_t			*threads;

	if (argc != 6 && argc != 5)
		ft_error("wrong number of args\n");
	ft_parsing(argc, argv, &data);
	forks = malloc(data.number_of_philosophers * sizeof(pthread_mutex_t));
	philosophers = malloc(data.number_of_philosophers * sizeof(t_philo));
	threads = malloc(data.number_of_philosophers * sizeof(pthread_t));
	if (!forks || !philosophers || !threads)
		ft_error("malloc issue!\n");
	ft_init_forks(forks, data);
	ft_init_philosophers(philosophers, data, forks);
	ft_start_routines(threads, philosophers, data);
	ft_destroy_mutex(forks, philosophers);
	return (free(forks), free(philosophers), free(threads), 0);
}
