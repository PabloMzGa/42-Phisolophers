/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/07/07 22:42:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * TODO: Ahora por alguna razón el programa no termina lo suficientemente
 * después de moprir un filósofo, pudiendo el mismo filósofo morir varias veces.
 *
 * Podrías er que se lanzan más hilos de la cuenta o vete tu a saber. También
 * se queda bloqueado a veces. Quizás valgrind ayude
*/


/**
 * @brief Initializes the program arguments and optionally starts the full
 * monitor thread.
 *
 * This function checks the validity of the command-line arguments, sets up
 * the program arguments structure, and, if the number of required eats
 * (`n_eat`) is greater than zero, creates a monitoring thread to track when
 * all philosophers have eaten enough times.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @param args The structure to store parsed program arguments.
 * @param full_monitor_id The thread identifier for the full monitor thread.
 * @return int Returns 0 on success, or 1 on failure (invalid arguments,
 * failed setup, or thread creation error).
 */
static int	init(int argc, char *argv[], t_args *args,
			pthread_t *full_monitor_id)
{
	if (!check_args(argc, argv))
		return (1);
	if (set_args(args, argc, argv))
		return (1);
	if (args->n_eat > 0)
	{
		if (pthread_create(full_monitor_id, NULL, full_monitor, args) != 0)
		{
			printf(RED "Error: Failed to create death stop monitor thread\n"
				RESET);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args		args;
	t_philo		*philo;
	pthread_t	full_monitor_id;

	if (init(argc, argv, &args, &full_monitor_id))
		return (1);
	philo = philo_start(&args);
	if (!philo)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		pthread_join(full_monitor_id, NULL);
		close_args_sems(&args);
	}
	else
	{
		safe_sem_wait(philo->death_monitor_end_sem);
		clean_philos(philo);
	}
	return (0);
}
