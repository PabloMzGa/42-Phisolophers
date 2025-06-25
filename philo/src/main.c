/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 18:08:04 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Initializes the simulation arguments and mutexes.
 *
 * This function parses command-line arguments to set up the simulation
 * parameters in the provided t_args structure. It initializes the number
 * of philosophers, time to die, time to eat, time to sleep, and optionally
 * the number of times each philosopher must eat. It also records the
 * simulation start epoch and sets the simulation running flag. Additionally,
 * it initializes the required mutexes for simulation control and output
 * synchronization.
 *
 * @param args Pointer to the t_args structure to be initialized.
 * @param argc Argument count from the command line.
 * @param argv Argument vector from the command line.
 * @return int Returns 0 on success, or 1 if mutex initialization fails.
 */
static int	set_args(t_args *args, int argc, char *argv[])
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
	args->simulation_running = 1;
	if (pthread_mutex_init(&args->simulation_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->printf_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&args->simulation_mutex);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*philos;

	if (!check_args(argc, argv))
		return (1);
	if (set_args(&args, argc, argv))
		return (1);
	philos = populate_philosophers(&args);
	start_philosophers_behaviour(philos);
	clean_philos(&philos);
	pthread_mutex_destroy(&args.printf_mutex);
	pthread_mutex_destroy(&args.simulation_mutex);
}
