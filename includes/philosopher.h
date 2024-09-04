/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:36:25 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/04 12:33:40 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H 
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

//struct

typedef struct s_data
{
	int	number_of_philosophers;
	long int time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	size_t	init_timestamp;
	
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *print_mutex;
	pthread_mutex_t *dead_mutex;
	int		index;
	int		dead;
	int		number_of_meals;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	time_to_die;
	int		number_of_philosophers;
	int		number_of_times_each_philosopher_must_eat;
	size_t	last_eating_time; 
	size_t	init_timestamp;
}	t_philo;

enum print_flags
{
	DEAD,
	EAT,
	SLEEP,
	FORK,
	THINK,
};
//atoi
int	ft_atoi(const char *str);
//error
void	ft_error(char *error_message);
//other
void *ft_monitoring(void *args);
void	ft_print_mutex(int flag, t_philo *philo);
size_t	get_current_time(void);
void	ft_init_forks(pthread_mutex_t *forks, t_data data);
void	ft_init_philosophers(t_philo *philosophers, t_data data, pthread_mutex_t *forks);
void	ft_start_routines(pthread_t *threads, t_philo *philosophers, t_data data);
int	ft_usleep(size_t milliseconds);

#endif