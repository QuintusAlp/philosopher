/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:11:01 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/10 20:21:27 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *error_message)
{
	write (2, error_message, ft_strlen(error_message));
	return (1);
}
