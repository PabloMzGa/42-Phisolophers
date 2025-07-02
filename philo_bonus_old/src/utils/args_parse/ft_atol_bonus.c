/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:23:00 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/25 14:21:49 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	ft_atol(const char *nptr)
{
	long	output;
	char	negative;

	output = 0;
	negative = 1;
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '-')
	{
		negative = -1;
		++nptr;
	}
	else if (*nptr == '+')
		++nptr;
	while (ft_isdigit(*nptr))
	{
		output = output * 10 + *nptr - '0';
		++nptr;
	}
	return (output * negative);
}
