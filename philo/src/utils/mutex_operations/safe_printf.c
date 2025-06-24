/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:50:34 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/24 12:11:52 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int safe_single_printf(char *string, t_args *args)
{
	if (safe_mutex_lock(&args->pritnf_mutex, args))
		return (1);
	printf("%s", string);
	if (safe_mutex_unlock(&args->pritnf_mutex, args))
		return (1);
	return (0);
}

int safe_log_printf(char *string, long timestamp, size_t id, t_args *args)
{
	if (safe_mutex_lock(&args->pritnf_mutex, args))
		return (1);
	printf(string, timestamp, id);
	if (safe_mutex_unlock(&args->pritnf_mutex, args))
		return (1);
	return (0);
}
