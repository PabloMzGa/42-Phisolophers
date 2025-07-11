/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:31:19 by pablo             #+#    #+#             */
/*   Updated: 2025/07/11 13:25:24 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
 * @brief Initializes the 'full_sem' semaphore in the given args structure.
 *
 * This function creates (or opens if already existing) a named semaphore
 * "/full_sem" with initial value 0 and permissions 0644, and assigns it to
 * args->full_sem. If the semaphore creation fails, it closes any previously
 * opened semaphores (forks_sem, printf_sem, stop_sem, grabbing_forks_sem)
 * and returns 1 to indicate error. On success, it unlinks the named semaphore
 * (so it is removed after all processes close it) and returns 0.
 *
 * @param args Pointer to the t_args structure where the semaphore will be
 *             stored.
 * @return int 0 on success, 1 on error.
 */
static int	set_full_sem(t_args *args)
{
	args->full_sem = sem_open("/full_sem", O_CREAT, 0644, 0);
	if (args->full_sem == SEM_FAILED)
		return (sem_close(args->forks_sem), sem_close(args->printf_sem),
			sem_close(args->stop_sem), sem_close(args->grabbing_forks_sem),
			1);
	sem_unlink("/full_sem");
	return (0);
}

/**
 * @brief Initializes and sets up the named POSIX semaphores required for the
 * program.
 *
 * This function creates and opens several named semaphores used for
 * synchronization between philosopher processes:
 *
 *   - forks_sem: Controls access to the forks (number of philosophers).
 *
 *   - printf_sem: Ensures atomic printing to the console.
 *
 *   - stop_sem: Signals when the simulation should stop.
 *
 *   - grabbing_forks_sem: Synchronizes fork grabbing.
 *
 * If the number of times each philosopher must eat (n_eat) is greater than 0,
 * it also initializes an additional semaphore for tracking full philosophers.
 *
 * All semaphores are unlinked immediately after creation to ensure they are
 * removed when no longer in use. If any semaphore fails to open, previously
 * opened semaphores are closed and an error is returned.
 *
 * @param args Pointer to the arguments structure where semaphore handles are
 *             stored.
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
	args->grabbing_forks_sem = sem_open("/grabbing_forks_sem", O_CREAT, 0644,
			args->philo_n / 2 + 1);
	if (args->grabbing_forks_sem == SEM_FAILED)
		return (sem_close(args->forks_sem), sem_close(args->printf_sem),
			sem_close(args->stop_sem), 1);
	sem_unlink("/grabbing_forks_sem");
	if (args->n_eat > 0)
		return (set_full_sem(args));
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
