/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/24 17:07:13 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"


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
	args->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, args->philo_n);
	if (args->forks_sem = SEM_FAILED)
		return (free(args), NULL);
	args->full_sem = sem_open("/full_sem", O_CREAT, 0644, args->philo_n);
	if (args->forks_sem = SEM_FAILED)
		return (sem_unlink("/forks_sem"), free(args), NULL);
	args->stop_sem = sem_oepn("/stop_sem", O_CREAT, 0644, 0);
	if (args->stop_sem = SEM_FAILED)
		return (sem_unlink("/forks_sem"), sem_unlink("/full_sem"), free(args),
			NULL);
	return (args);
}

int	main(int argc, char *argv[])
{
	t_args	*args;
	t_philo	*philo;

	if (!check_args(argc, argv))
		return (1);
	args = set_args(argc, argv);
	if (!args)
		return (1);
	philo = populate_philosophers(args);
	if (philo)
		start_philosophers_behaviour(philo);
	else
	{
		// TODO: Hacer una espera, ya sea con semáforo o con waitpid
		sem_unlink("/forks_sem");
		sem_unlink("/end_sem");
		free(args);
		args = NULL;
	}
}
