/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 20:11:42 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Allocates and initializes a t_args structure with command-line
 * arguments.
 *
 * This function parses the command-line arguments and fills a newly allocated
 * t_args structure with the corresponding values:
 *
 *   - philo_n:    Number of philosophers (from argv[1])
 *
 *   - time_die:   Time to die (from argv[2])
 *
 *   - time_eat:   Time to eat (from argv[3])
 *
 *   - time_sleep: Time to sleep (from argv[4])
 *
 *   - n_eat:      Number of times each philosopher must eat (from argv[5],
 *                 optional; set to -1 if not provided)
 *
 * @param argc The argument count from main.
 * @param argv The argument vector from main.
 * @return Pointer to the initialized t_args structure, or NULL on allocation
 *         failure.
 */
static t_args	*set_args(int argc, char *argv[])
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->philo_n = ft_atosize_t(argv[1]);
	args->time_die = ft_atol(argv[2]);
	args->time_eat = ft_atosize_t(argv[3]);
	args->time_sleep = ft_atosize_t(argv[4]);
	if (argc == 6)
		args->n_eat = ft_atoi(argv[5]);
	else
		args->n_eat = -1;
	args->epoch = get_time_ms();
	args->simulation_running = 1;
	if (pthread_mutex_init(&args->simulation_mutex, NULL) != 0)
		return (free(args), NULL);
	return (args);
}

int	main(int argc, char *argv[])
{
	t_args	*args;
	t_philo	*philos;

	if (!check_args(argc, argv))
		return (1);
	args = set_args(argc, argv);
	if (!args)
		return (1);
	philos = populate_philosophers(args);
	start_philosophers_behaviour(philos);
	clean_philos(&philos);
	free(args);
	args = NULL;
}
