/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:48:49 by adardour          #+#    #+#             */
/*   Updated: 2023/06/16 15:34:24 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo_node	*ft_lstnew(t_data *data, int id)
{
	t_philo_node	*new_tlist;

	new_tlist = NULL;
	new_tlist = (t_philo_node *)malloc(sizeof(t_philo_node));
	if (new_tlist == NULL)
		return (NULL);
	new_tlist->id = id;
	new_tlist->next = NULL;
	new_tlist->start_time = 0;
	new_tlist->data = *data;
	return (new_tlist);
}

void	ft_lstadd_front(t_philo_node **lst, t_philo_node *new)
{
	new->next = *lst;
	*lst = new;
}

void	create_node(int number_philo, t_philo_node **head, t_data *data)
{
	t_philo_node	*new;

	new = ft_lstnew(data, number_philo);
	ft_lstadd_front(head, new);
}

t_philo_node	*init_nodes(int number_philo, t_data *data)
{
	t_philo_node	*head;

	head = NULL;
	while (number_philo)
	{
		create_node(number_philo, &head, data);
		number_philo--;
	}
	return (head);
}

void	init_args(t_data *data, char **args, int c)
{
	data->number_of_philosophers = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (c == 6)
		data->number_of_eat = ft_atoi(args[5]);
	else
		data->number_of_eat = -1;
}
