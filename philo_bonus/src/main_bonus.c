/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/07/08 14:01:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

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
	int			philo_status;
	pthread_t	full_monitor_id;

	full_monitor_id = 0;
	if (init(argc, argv, &args, &full_monitor_id))
		return (1);
	philo_status = philo_start(&args);
	if (!philo_status)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		if (full_monitor_id)
			pthread_join(full_monitor_id, NULL);
		close_args_sems(&args);
	}
	return (0);
}
