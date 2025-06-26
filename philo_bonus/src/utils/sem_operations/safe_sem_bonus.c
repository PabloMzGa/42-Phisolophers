/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_sem_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:40:55 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 20:58:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

// TODO: Buscar la forma de detener la simulación si falla. ¿Exit quizás?
// De esa forma el padre podría matar al resto de procesos.

int	safe_sem_wait(sem_t *sem)
{
	int	status;

	status = sem_wait(sem);
	if (status != 0)
	{
		printf(RED "Error: sem_wait failed with code %d\n" RESET, status);
		return (1);
	}
	return (0);
}

int	safe_sem_post(sem_t *sem)
{
	int	status;

	//TODO: Helgrind dice que hay veces que se hace el post estando sem en NULL
	//Tengo que averiguar en que momento pasa eso, y de ser relevante,
	//controlar el error con return 1.
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
