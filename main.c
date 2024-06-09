/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:54:26 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/06/08 22:11:37 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	waiting_processes(t_table *table, int i)
{
	if (start_threads(table, -1) == FALSE)
		return (FALSE);
	while (++i < table->philo_number)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (printf(JOIN), FALSE);
	}
	if (table->check_die)
		printf("%llu	Philo id: %d  %s\n", table->die_time, table->die_id,
			DIED);
	return (TRUE);
}

void	*just_one_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->table->onset = get_time();
	pthread_mutex_lock(&philo->table->mutex_chopstick[philo->left_chopstick]);
	write_all(L_CHOPSTICK, philo);
	pthread_mutex_unlock(&philo->table->mutex_chopstick[philo->left_chopstick]);
	philo_sleep(philo->table->time_to_die);
	write_all(DIED, philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (input_control(ac, av, &table) == FALSE)
		return (FALSE);
	if (create_philo(&table) == FALSE)
		return (FALSE);
	if (create_chopstick_and_mutex(&table) == FALSE)
		return (free_and_destroy(&table), FALSE);
	if (table.philo_number == 1)
	{
		if (pthread_create(&table.philo[0].thread, NULL, &just_one_philo,
				&table.philo[0]) != 0)
			return (printf(CREATE), free_and_destroy(&table), FALSE);
		if (pthread_join(table.philo[0].thread, NULL) != 0)
			return (printf(CREATE), free_and_destroy(&table), FALSE);
		return (free_and_destroy(&table), TRUE);
	}
	if (waiting_processes(&table, -1) == FALSE)
		return (free_and_destroy(&table), FALSE);
	return (free_and_destroy(&table), TRUE);
}
