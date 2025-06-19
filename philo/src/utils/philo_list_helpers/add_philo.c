/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:24:26 by pablo             #+#    #+#             */
/*   Updated: 2025/06/19 13:55:08 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Adds a new philosopher node to the end of the philosopher list.
 *
 * This function appends the given 'new' philosopher node to the end of the
 * doubly linked list pointed to by 'philo_lst'. If the list is empty,
 * 'new' becomes the first node. If either 'philo_lst' or 'new' is NULL,
 * the function does nothing.
 *
 * @param philo_lst Pointer to the head pointer of the philosopher list.
 * @param new Pointer to the new philosopher node to be added.
 */
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
	new->previous = temp;
}
