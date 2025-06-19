/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atosize_t.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:23:00 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/19 13:11:45 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_atosize_t(const char *nptr)
{
	size_t	output;

	output = 0;
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '-')
		return (0);
	else if (*nptr == '+')
		++nptr;
	while (ft_isdigit(*nptr))
	{
		output = output * 10 + *nptr - '0';
		++nptr;
	}
	return (output );
}
