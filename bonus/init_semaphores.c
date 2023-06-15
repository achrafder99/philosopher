/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 02:22:05 by adardour          #+#    #+#             */
/*   Updated: 2023/06/15 02:27:50 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	int_semaphores(sem_t *inital_semaphore, sem_t *print,
		int number_of_philo)
{
	sem_unlink("/semaphore");
	sem_unlink("/print");
	inital_semaphore = sem_open("/semaphore", O_CREAT | O_EXCL | O_RDWR, 0666,
			number_of_philo);
	print = sem_open("/print", O_CREAT | O_EXCL | O_RDWR, 0666, 1);
	if (!inital_semaphore)
	{
		printf("Semaphore error\n");
		exit(EXIT_FAILURE);
	}
}
