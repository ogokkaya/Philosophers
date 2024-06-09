/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:24:00 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/06/08 21:37:25 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf(TIME);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	philo_sleep(u_int64_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(250);
}
