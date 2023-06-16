/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:01:19 by adardour          #+#    #+#             */
/*   Updated: 2023/06/16 15:37:01 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int	main(int c, char **argv)
{
	t_data			*data;
	t_philo_node	*head;
	t_philo_node	*temp;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (c <= 4 || c > 6 || !parse(argv))
	{
		write(2, "Error Parsing\n", 15);
		return (1);
	}
	if (ft_atoi(argv[1]) == 0)
	{
		printf("One or more philosophers sit at a round table.\n");
		return (0);
	}
	init_args(data, argv, c);
	head = init_nodes(data->number_of_philosophers, data);
	temp = head;
	to_do_bonus(temp, data->number_of_philosophers);
	kill_all(head);
	free(data);
}
