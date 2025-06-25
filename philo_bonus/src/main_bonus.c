/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 18:48:49 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

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
	args->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, args->philo_n);
	if (args->forks_sem == SEM_FAILED)
		return (free(args), 1);
	args->full_sem = sem_open("/full_sem", O_CREAT, 0644, args->philo_n);
	if (args->forks_sem == SEM_FAILED)
		return (sem_unlink("/forks_sem"), free(args), 1);
	args->death_sem = sem_open("/death_sem", O_CREAT, 0644, 0);
	if (args->death_sem == SEM_FAILED)
		return (sem_unlink("/forks_sem"), sem_unlink("/full_sem"), free(args),
			1);
	return (0);
}

// TODO: Proteger los printf con un mutex

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*philo;

	if (!check_args(argc, argv))
		return (1);
	if (set_args(&args, argc, argv))
		return (1);
	philo = populate_philosophers(&args);
	if (philo)
		start_philosophers_behaviour(philo);
	else
	{
		// TODO: Hacer una espera, ya sea con semáforo o con waitpid
		sem_unlink("/forks_sem");
		sem_unlink("/end_sem");
	}
}
