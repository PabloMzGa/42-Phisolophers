/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:31:19 by pablo             #+#    #+#             */
/*   Updated: 2025/07/04 14:14:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * TODO: Parece que hay un error con stop_sem. Por alguna razón dice
 * que el semáforo es inválido. Puede que sea porque al hacer close
 * como la referencia es la misma en args, un sólo close sea ya suficiente
 *
 * Entonces, o bien se libera solo en el padre (no creo), o cada hijo
 * debe hacer su propio sem_open para tener una referencia individual
 * al semáforo.
 *
 * Sin embargo, al comentar la limpieza, sigue dando error. Asi que puede que
 * sea por algo relacionado con su creación.
 */
int	set_sems(t_args *args)
{
	args->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, args->philo_n);
	if (args->forks_sem == SEM_FAILED)
		return (1);
	sem_unlink("/forks_sem");
	args->printf_sem = sem_open("/printf_sem", O_CREAT, 0644, 1);
	if (args->printf_sem == SEM_FAILED)
		return (sem_close(args->forks_sem), 1);
	sem_unlink("/printf_sem");
	args->stop_sem = sem_open("/stop_sem", O_CREAT, 0644, 0);
	if (args->stop_sem == SEM_FAILED)
		return (sem_close(args->forks_sem), sem_close(args->printf_sem), 1);
	sem_unlink("/stop_sem");
	if (args->n_eat > 0)
	{
		args->full_sem = sem_open("/full_sem", O_CREAT, 0644, 0);
		if (args->full_sem == SEM_FAILED)
			return (sem_close(args->forks_sem), sem_close(args->printf_sem),
				sem_close(args->stop_sem), 1);
		sem_unlink("/full_sem");
	}
	return (0);
}

int	set_args(t_args *args, int argc, char *argv[])
{
	// Initialize semaphore pointers to NULL
	args->forks_sem = NULL;
	args->printf_sem = NULL;
	args->stop_sem = NULL;
	args->full_sem = NULL;

	args->philo_n = ft_atoui(argv[1]);
	args->time_die = ft_atoui(argv[2]);
	args->time_eat = ft_atoui(argv[3]);
	args->time_sleep = ft_atoui(argv[4]);
	if (argc == 6)
		args->n_eat = ft_atoui(argv[5]);
	else
		args->n_eat = 0;
	args->epoch = get_time_ms();
	return (set_sems(args));
}
