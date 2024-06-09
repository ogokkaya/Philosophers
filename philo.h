/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:54:29 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/06/08 21:32:00 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FALSE 1
# define TRUE 0

# include <pthread.h>

// Help
# define HELP \
	"The number of argments must be 4 or 5:\n\
- arg1 number of philosophers\n\
- arg2 time to die\n\
- arg3 time to eat\n\
- arg4 time to sleep\n\
- arg5 number of times each philosopher must eat (optional)"

// unsual
# define MALLOC "Error\nMemory allocation failed\n"
# define MUTEX "Error\nCould not create mutex\n"
# define TIME "Error\nCould not get time\n"
# define JOIN "Error\nThread waiting not be done\n"
# define CREATE "Error\nCould not create thread\n"
# define ARG_NUM \
	"Error\n5 arguments are required for the program to run \
(6th argument is optional)"
# define ARG_1 "Error\nThere is a mistake in number of philosophers"
# define ARG_2 "Error\nThere is a mistake in time to die"
# define ARG_3 "Error\nThere is a mistake in time to eat"
# define ARG_4 "Error\nThere is a mistake in time to sleep"
# define ARG_5 \
	"Error\nThere is a mistake in number of times each \
philosopher must eat"

// usaul
# define R_CHOPSTICK "right chopstick"
# define L_CHOPSTICK "left chopstick"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thiking"
# define DIED "is died"

typedef struct s_philo
{
	int				philo_id;
	u_int64_t		last_eat;
	pthread_t		thread;
	size_t			eat_count;
	int				left_chopstick;
	int				right_chopstick;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	t_philo			*philo;
	int				philo_number;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			eat_limit;
	int				die_id;
	int				eat_count;
	int				check_die;
	u_int64_t		die_time;
	u_int64_t		onset;
	pthread_mutex_t	mutex_wait;
	pthread_mutex_t	*mutex_chopstick;
	pthread_mutex_t	mutex_print_and_time;
}					t_table;

int					input_control(int ac, char **av, t_table *table);
int					create_chopstick_and_mutex(t_table *table);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strlen(char *str);
void				free_and_destroy(t_table *table);
int					create_philo(t_table *table);
int					die_control(t_table *table, t_philo *philo, int i);
int					write_all(char *str, t_philo *philo);
void				philo_sleep(u_int64_t time);
u_int64_t			get_time(void);
int					start_threads(t_table *table, int i);
int					ft_philo_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);

#endif