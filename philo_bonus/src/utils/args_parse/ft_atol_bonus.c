/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:23:00 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/22 22:32:13 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
