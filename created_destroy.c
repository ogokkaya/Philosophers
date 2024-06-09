/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:52:46 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/06/08 21:23:39 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	free_and_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_number)
	{
		if (&table->mutex_chopstick[i])
			pthread_mutex_destroy(&table->mutex_chopstick[i]);
	}
	if (table->mutex_chopstick)
		free(table->mutex_chopstick);
	if (table->philo)
		free(table->philo);
	table->philo = NULL;
	table->mutex_chopstick = NULL;
	pthread_mutex_destroy(&table->mutex_print_and_time);
	pthread_mutex_destroy(&table->mutex_wait);
}
