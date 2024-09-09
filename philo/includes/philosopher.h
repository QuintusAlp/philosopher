/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:36:25 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/09 15:49:35 by qalpesse         ###   ########.fr       */
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
	int				number_of_philosophers;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	size_t			init_timestamp;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*eat_mutex;
	int				is_eating;
	int				index;
	int				dead;
	int				number_of_meals;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	size_t			last_eating_time;
	size_t			init_timestamp;
}	t_philo;

enum e_print_flags
{
	DEAD,
	EAT,
	SLEEP,
	FORK,
	THINK,
};

//error
void	ft_error(char *error_message);
//init
void	ft_init_philosophers(t_philo *philosophers, t_data *data);
int		ft_init_mutex(t_data *data);
void	ft_destroy(pthread_mutex_t *mutexs, int j);
int		ft_init_malloc_mutex(pthread_mutex_t *mutexs, t_data *data);
//others
size_t	ft_current_time(void);
int		ft_start_routines(pthread_t *threads, t_philo *philo);
void	ft_print_mutex(int flag, t_philo *philo);
int		ft_usleep(size_t milliseconds);
int		ft_philo_is_dead(t_philo *philo);
//monitoring
int		ft_nbr_full_philo(t_philo *philo);
int		ft_check_death(t_philo *philo);
void	ft_kill_all_philo(t_philo *philo);
void	*ft_monitoring(void *arg);
void	*ft_monitoring(void *arg);
//utils
int		ft_atoi(const char *str);
size_t	ft_current_time(void);
int		ft_usleep(size_t milliseconds);
void	ft_print_mutex(int flag, t_philo *philo);

#endif