/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:29:57 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/08 12:37:03 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

size_t	ft_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_error("gettimeofday error\n"), 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_current_time();
	while ((ft_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}


void	ft_print_mutex(int flag, t_philo *philo)
{
	(void)flag;
	(void)philo;
	if (!philo->dead)
	{
		pthread_mutex_lock(philo->print_mutex);
		if (flag == EAT)
			printf("%zu %d is eating... miam miam\n",ft_current_time() - philo->init_timestamp, philo->index);
		if (flag == FORK)
			printf("%zu %d has taken a fork\n",ft_current_time() - philo->init_timestamp, philo->index);
		if (flag == THINK)
			printf("%zu %d is thinking... hmmm\n",ft_current_time() - philo->init_timestamp, philo->index);
		if (flag == SLEEP)
			printf("%zu %d is sleeping... zzzzzz\n",ft_current_time() - philo->init_timestamp, philo->index);
		if (flag == DEAD)
			printf("\033[31m%zu %d died... miskine\033[0m\n",ft_current_time() - philo->init_timestamp, philo->index);
		pthread_mutex_unlock(philo->print_mutex);
	}
	return ;
}

int	ft_parsing(int	argc, char **argv,t_data *data)
{
	if (argc != 6 && argc != 5)
		return(ft_error("wrong number of args\n"), 1);
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
	while(i < philo->number_of_philosophers)
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
	pthread_t			*threads;
	pthread_mutex_t	*forks;

	if (ft_parsing(argc, argv, &data))
		return (1);
	philosophers = malloc(data.number_of_philosophers * sizeof(t_philo));
	if (!philosophers)
		return(ft_error("malloc erro\n"), 1);
	forks = malloc(data.number_of_philosophers * sizeof(pthread_mutex_t));
	if (!forks)
		return(ft_error("malloc erro\n"), 1);
	threads = malloc(data.number_of_philosophers * sizeof(pthread_t));
	if (!threads)
		return(ft_error("malloc erro\n"), 1);
	ft_init_mutex(forks, &data);
	ft_init_philosophers(philosophers, &data, forks);
	if (ft_start_routines(threads, philosophers))
		return (1);
	ft_destroy_all(forks, philosophers);
	free(philosophers);
	free(forks);
	free(threads);
}
