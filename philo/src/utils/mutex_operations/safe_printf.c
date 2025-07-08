/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:50:34 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/08 14:05:42 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	safe_single_printf(char *string, t_args *args)
{
	if (safe_mutex_lock(&args->printf_mutex, args))
		return (1);
	printf("%s", string);
	if (safe_mutex_unlock(&args->printf_mutex, args))
		return (1);
	return (0);
}

int	safe_log_printf(char *string, unsigned int id, t_args *args)
{
	if (safe_mutex_lock(&args->printf_mutex, args))
		return (1);
	printf(string, get_time_ms() - args->epoch, id);
	if (safe_mutex_unlock(&args->printf_mutex, args))
		return (1);
	return (0);
}
