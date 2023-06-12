/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:25:51 by adardour          #+#    #+#             */
/*   Updated: 2023/06/11 18:22:40 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int	parse(char **args)
{
	int	i;
	int	j;

	i = 1;
	if (args[i] == NULL)
		return (0);
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (!ft_isdigit(args[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
