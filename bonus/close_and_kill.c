/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_kill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 02:19:39 by adardour          #+#    #+#             */
/*   Updated: 2023/06/15 02:20:32 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	close_and_kill(t_philo_node *head, sem_t *inital_semaphore,
		sem_t *print)
{
	kill_all(head);
	sem_close(inital_semaphore);
	sem_close(print);
	sem_unlink("/semaphore");
	sem_unlink("/print");
}
