/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_check_and_write.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:55:05 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/06/08 22:11:33 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	write_all(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mutex_print_and_time);
	if (philo->table->check_die != 1)
	{
		printf("%llu	Philo id: %d  %s\n", get_time() - philo->table->onset,
			philo->philo_id, str);
		pthread_mutex_unlock(&philo->table->mutex_print_and_time);
		return (TRUE);
	}
	return (pthread_mutex_unlock(&philo->table->mutex_print_and_time), FALSE);
}

int	die_control(t_table *table, t_philo *philo, int i)
{
	pthread_mutex_lock(&table->mutex_print_and_time);
	if ((get_time() - philo->last_eat) >= table->time_to_die)
	{
		table->check_die = 1;
		table->die_id = i + 1;
		table->die_time = get_time() - table->onset;
		pthread_mutex_unlock(&table->mutex_print_and_time);
		return (FALSE);
	}
	pthread_mutex_unlock(&table->mutex_print_and_time);
	return (TRUE);
}
