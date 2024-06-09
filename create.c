/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:54:20 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/06/08 21:23:47 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	create_philo(t_table *table)
{
	int	i;

	table->philo = (t_philo *)ft_calloc(table->philo_number, sizeof(t_philo));
	if (!table->philo)
		return (printf("%s\n", MALLOC), FALSE);
	i = 0;
	table->onset = get_time();
	while (i < table->philo_number)
	{
		table->philo[i].left_chopstick = i;
		table->philo[i].right_chopstick = (i + 1) % table->philo_number;
		table->philo[i].philo_id = i + 1;
		table->philo[i].table = table;
		table->philo[i].last_eat = table->onset;
		i++;
	}
	return (TRUE);
}

int	create_chopstick_and_mutex(t_table *table)
{
	int	i;

	table->mutex_chopstick = (pthread_mutex_t *)ft_calloc(table->philo_number,
			sizeof(pthread_mutex_t));
	if (!table->mutex_chopstick)
		return (printf(MALLOC), FALSE);
	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(&table->mutex_chopstick[i], NULL))
			return (printf(MUTEX), FALSE);
		i++;
	}
	if (pthread_mutex_init(&table->mutex_print_and_time, NULL) != 0)
		return (printf(MUTEX), FALSE);
	if (pthread_mutex_init(&table->mutex_wait, NULL) != 0)
		return (printf(MUTEX), FALSE);
	table->check_die = 0;
	table->eat_count = 0;
	return (TRUE);
}
