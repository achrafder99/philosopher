/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 02:11:04 by adardour          #+#    #+#             */
/*   Updated: 2023/06/15 02:11:17 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	kill_all(t_philo_node *head)
{
	t_philo_node	*philo;

	philo = head;
	while (philo)
	{
		kill(philo->pid, SIGKILL);
		philo = philo->next;
	}
}
