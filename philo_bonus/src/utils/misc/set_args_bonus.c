/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:31:19 by pablo             #+#    #+#             */
/*   Updated: 2025/07/07 17:44:56 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Initializes and unlinks named POSIX semaphores used by the program.
 *
 * This function creates and opens several named semaphores required for
 * synchronization:
 *
 *   - "/forks_sem": Controls access to forks (initialized to the number of
 *     philosophers).
 *
 *   - "/printf_sem": Ensures exclusive access to printing (initialized to 1).
 *
 *   - "/stop_sem": Used to signal stopping condition (initialized to 0).
 *
 *   - "/full_sem": (Optional) Used if n_eat > 0, to track philosophers who
 *     have eaten enough (initialized to 0).
 *
 * Each semaphore is unlinked immediately after creation to ensure it is
 * removed from the system when all processes close it. If any semaphore fails
 * to open, previously opened semaphores are closed, and the function returns 1
 * to indicate failure.
 *
 * @param args Pointer to a t_args structure containing program arguments and
 *             semaphore handles.
 * @return 0 on success, 1 on failure.
 */
static int	set_sems(t_args *args)
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
