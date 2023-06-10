/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_own_usleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:43:55 by adardour          #+#    #+#             */
/*   Updated: 2023/06/09 19:33:21 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_own_usleep22(long long time_stamps)
{
	long long	current;

	current = current_time();
	while (current_time() - current < time_stamps)
		usleep(50);
}
