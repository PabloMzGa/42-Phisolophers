/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:24:26 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 19:25:49 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	add_philo(t_philo **philo_lst, t_philo *new)
{
	t_philo	*temp;

	if (!philo_lst || !new)
		return ;
	if (*philo_lst == NULL)
	{
		*philo_lst = new;
		return ;
	}
	temp = *philo_lst;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
}
