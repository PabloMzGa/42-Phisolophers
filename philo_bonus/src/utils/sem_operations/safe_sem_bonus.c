/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_sem_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:40:55 by pablo             #+#    #+#             */
/*   Updated: 2025/07/07 21:10:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

int	safe_sem_wait(sem_t *sem)
{
	int	status;

	if (sem)
	{
		status = sem_wait(sem);
		if (status != 0)
		{
			printf(RED "Error: sem_wait failed with code %d\n" RESET, status);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	safe_sem_post(sem_t *sem)
{
	int	status;
	if (sem)
	{
		status = sem_post(sem);
		if (status != 0)
		{
			printf(RED "Error: sem_post failed with code %d\n" RESET, status);
			return (1);
		}
	}
	return (0);
}
