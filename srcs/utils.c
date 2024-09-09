/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:15:40 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/09 08:27:30 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	is_neg;
	int	res;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		is_neg = -1;
	else
		is_neg = 1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if (sizeof(res) >= sizeof(long long))
			return (-1);
	}
	return (res * is_neg);
}

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
	size_t	current_time_value;
	int		i;

	current_time_value = ft_current_time() - philo->init_timestamp;
	i = philo->index + 1;
	if (!philo->dead)
	{
		pthread_mutex_lock(philo->print_mutex);
		if (flag == EAT)
			printf("%zu %d is eating... miam miam\n", current_time_value, i);
		if (flag == FORK)
			printf("%zu %d has taken a fork\n", current_time_value, i);
		if (flag == THINK)
			printf("%zu %d is thinking... hmmm\n", current_time_value, i);
		if (flag == SLEEP)
			printf("%zu %d is sleeping... zzzzzz\n", current_time_value, i);
		if (flag == DEAD)
			printf("\033[31m%zu %d died...\033[0m\n", current_time_value, i);
		pthread_mutex_unlock(philo->print_mutex);
	}
	return ;
}
