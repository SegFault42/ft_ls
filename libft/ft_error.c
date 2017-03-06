/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:14:04 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/02 15:24:18 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_error(uint8_t error)
{
	if (error == MALLOC_ERROR)
		ft_dprintf(STDERR_FILENO, RED"Memory allocation failure !\n"END);
	exit (EXIT_FAILURE);
}
