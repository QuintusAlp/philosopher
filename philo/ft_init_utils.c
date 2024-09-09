/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:39 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/09 15:58:06 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

void	ft_destroy(pthread_mutex_t *mutexs, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&mutexs[i]);
		i++;
	}
	free(mutexs);
}

int	ft_init_malloc_mutex(pthread_mutex_t *mutexs, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&mutexs[i], NULL))
			return (ft_destroy(mutexs, i), 1);
		i++;
	}
	return (0);
}
