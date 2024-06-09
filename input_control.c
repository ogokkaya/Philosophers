/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:17:15 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/06/08 21:06:09 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	arguman_control(t_table *table)
{
	if (!table->philo_number)
		printf("%s\n", ARG_1);
	if (!table->time_to_die)
		printf("%s\n", ARG_2);
	if (!table->time_to_eat)
		printf("%s\n", ARG_3);
	if (!table->time_to_sleep)
		printf("%s\n", ARG_4);
	if (!table->eat_limit)
		printf("%s\n", ARG_5);
}

static int	struct_input(int ac, char **av, t_table *table)
{
	if (ac == 5 || ac == 6)
	{
		table->philo_number = ft_philo_atoi(av[1]);
		table->time_to_die = ft_philo_atoi(av[2]);
		table->time_to_eat = ft_philo_atoi(av[3]);
		table->time_to_sleep = ft_philo_atoi(av[4]);
		if (ac == 6)
			table->eat_limit = ft_philo_atoi(av[5]);
		else
			table->eat_limit = -1;
		return (TRUE);
	}
	return (FALSE);
}

int	input_control(int ac, char **av, t_table *table)
{
	if (ac == 2 && !ft_strncmp(av[1], "help", 4) && ft_strlen(av[1]) == 4)
		return (printf("%s\n", HELP), FALSE);
	else if (struct_input(ac, av, table) == FALSE)
		return (printf("%s\n", ARG_NUM), FALSE);
	else
	{
		arguman_control(table);
		if (!table->philo_number || !table->time_to_die || !table->time_to_eat
			|| !table->time_to_sleep || !table->eat_limit)
			return (FALSE);
	}
	return (TRUE);
}
