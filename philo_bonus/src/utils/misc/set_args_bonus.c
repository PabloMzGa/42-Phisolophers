/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:31:19 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 18:51:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Initializes and sets up named POSIX semaphores for the program.
 *
 * This function creates and opens four named semaphores:
 *
 * - "/forks_sem": Represents the available forks (initialized to philo_n).
 *
 * - "/full_sem": Tracks philosophers who have eaten enough
 *    (initialized to philo_n).
 *
 * - "/death_sem": Signals a philosopher's death (initialized to 0).
 *
 * - "/stop_sem": Signals stopping the simulation (initialized to philo_n).
 *
 * - "/printf_sem": Controls the access to printf (initialized to 1).
 *
 * Each semaphore is unlinked immediately after creation to ensure it is
 * removed from the system once all processes have closed it. If any semaphore
 * fails to open, the function closes any previously opened semaphores and
 * returns 1 to indicate error.
 *
 * @param args Pointer to a t_args structure where semaphore handles will be
 *             stored.
 * @return 0 on success, 1 on failure.
 */
int	set_sems(t_args *args)
{
	args->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, args->philo_n);
	if (args->forks_sem == SEM_FAILED)
		return (1);
	sem_unlink("/forks_sem");
	args->full_sem = sem_open("/full_sem", O_CREAT, 0644, 0);
	if (args->full_sem == SEM_FAILED)
		return (sem_close(args->forks_sem), 1);
	sem_unlink("/full_sem");
	args->death_sem = sem_open("/death_sem", O_CREAT, 0644, 0);
	if (args->death_sem == SEM_FAILED)
		return (sem_close(args->forks_sem), sem_close(args->full_sem), 1);
	sem_unlink("/death_sem");
	args->stop_sem = sem_open("/stop_sem", O_CREAT, 0644, args->philo_n);
	if (args->stop_sem == SEM_FAILED)
		return (sem_close(args->forks_sem), sem_close(args->full_sem),
			sem_close(args->death_sem), 1);
	sem_unlink("/stop_sem");
	args->printf_sem = sem_open("/printf_sem", O_CREAT, 0644, args->philo_n);
	if (args->printf_sem == SEM_FAILED)
		return (sem_close(args->forks_sem), sem_close(args->full_sem),
			sem_close(args->death_sem),sem_close(args->stop_sem), 1);
	sem_unlink("/printf_sem");
	return (0);
}

int	set_args(t_args *args, int argc, char *argv[])
{
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
