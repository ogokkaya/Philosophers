/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operating_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:07:12 by ogokkaya			#+#    #+#            */
/*   Updated: 2024/06/08 17:50:31 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	mutex_unlock(t_table *table, t_philo *philo, int flag)
{
	if (flag == 0)
		pthread_mutex_unlock(&table->mutex_chopstick[philo->left_chopstick]);
	else if (flag == 1)
	{
		pthread_mutex_unlock(&table->mutex_chopstick[philo->left_chopstick]);
		pthread_mutex_unlock(&table->mutex_chopstick[philo->right_chopstick]);
	}
}

int	eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->mutex_chopstick[philo->left_chopstick]);
	if (write_all(L_CHOPSTICK, philo) == FALSE)
		return (mutex_unlock(table, philo, 0), FALSE);
	pthread_mutex_lock(&table->mutex_chopstick[philo->right_chopstick]);
	if (write_all(R_CHOPSTICK, philo) == FALSE)
		return (mutex_unlock(table, philo, 1), FALSE);
	if (write_all(EAT, philo) == FALSE)
		return (mutex_unlock(table, philo, 1), FALSE);
	philo_sleep(table->time_to_eat);
	pthread_mutex_lock(&table->mutex_print_and_time);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&table->mutex_print_and_time);
	mutex_unlock(table, philo, 1);
	philo->eat_count++;
	return (TRUE);
}

int	philo_cycle(t_philo *philo, t_table *table)
{
	if (eating(philo, table) == FALSE)
		return (FALSE);
	if (write_all(SLEEP, philo) == FALSE)
		return (FALSE);
	philo_sleep(philo->table->time_to_sleep);
	if (write_all(THINK, philo) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->philo_id % 2 != 0)
		philo_sleep(10);
	while (philo_cycle(philo, philo->table) == TRUE)
	{
		pthread_mutex_lock(&philo->table->mutex_wait);
		if (philo->eat_count == philo->table->eat_limit)
		{
			philo->table->eat_count++;
			pthread_mutex_unlock(&philo->table->mutex_wait);
			break ;
		}
		pthread_mutex_unlock(&philo->table->mutex_wait);
	}
	return (NULL);
}

int	start_threads(t_table *table, int i)
{
	while (++i < table->philo_number)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_life,
				&table->philo[i]) != 0)
			return (printf(CREATE), FALSE);
	}
	while (1)
	{
		i = -1;
		while (++i < table->philo_number)
		{
			pthread_mutex_lock(&table->mutex_wait);
			if (die_control(table, &table->philo[i], i) == FALSE
				|| table->eat_count == table->philo_number)
			{
				pthread_mutex_unlock(&table->mutex_wait);
				break ;
			}
			pthread_mutex_unlock(&table->mutex_wait);
		}
		philo_sleep(1);
		if (i != table->philo_number)
			break ;
	}
	return (TRUE);
}
