/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_kill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 02:19:39 by adardour          #+#    #+#             */
/*   Updated: 2023/06/16 12:15:58 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	close_and_kill(t_philo_node *head, sem_t *inital_semaphore,
		sem_t *print, sem_t *print_die)
{
	sem_close(inital_semaphore);
	sem_unlink("/semaphore");
	sem_close(print_die);
	sem_unlink("/print_die");
	sem_close(print);
	sem_unlink("/print");
	sem_close(print_die);
	kill_all(head);
}
