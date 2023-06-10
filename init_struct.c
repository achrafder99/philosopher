/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 23:32:38 by adardour          #+#    #+#             */
/*   Updated: 2023/06/09 19:49:04 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_philo_node	*allocate_philo(void)
{
	t_philo_node	*node;

	node = malloc(sizeof(t_philo_node));
	if (!node)
	{
		printf("Error: Failed to allocate memory!");
		return (NULL);
	}
	return (node);
}

void	create_node(int data, t_philo_node **head, t_data *data_node)
{
	t_philo_node	*current;
	t_philo_node	*node;

	node = allocate_philo();
	node->id = data;
	node->last_meal = 0;
	node->data = *data_node;
	node->start_time = 0;
	node->eat = 0;
	if (*head == NULL)
	{
		*head = node;
		node->next = node;
	}
	else
	{
		current = *head;
		while (current->next != *head)
			current = current->next;
		current->next = node;
		node->next = *head;
		*head = node;
	}
}

t_philo_node	*create_structs_for_philo(int number_philo, t_data *data)
{
	t_philo_node	*head;
	int				i;

	head = NULL;
	i = 0;
	while (number_philo >= 1)
	{
		create_node(number_philo, &head, data);
		number_philo--;
	}
	return (head);
}
