/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_own_usleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:43:55 by adardour          #+#    #+#             */
/*   Updated: 2023/06/15 02:04:23 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	my_own_usleep22(long long time_stamps, t_philo_node *current_philo)
{
	long long	current;

	current = current_time();
	while (current_time() - current < time_stamps)
	{
		if (check_death(current_philo))
			exit(1);
		usleep(50);
	}
}
