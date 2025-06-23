/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_simulation_running.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:55:00 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 22:34:28 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_simulation_running(t_args *args, int value)
{
	if (safe_mutex_lock(&args->simulation_mutex, NULL) == 0)
	{
		args->simulation_running = value;
		safe_mutex_unlock(&args->simulation_mutex, NULL);
	}
}
