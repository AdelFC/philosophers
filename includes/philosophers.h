/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:47:43 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/22 23:50:12 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*------------------- LIBS --------------------*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

/*------------------- STRUC --------------------*/

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				philo_id;
	long			last_meal_time;
	int				meals_counter;
	int				full;
	pthread_mutex_t	philo_mtx;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_table			*table;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_table
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_max_meals;
	int				end_simulation;
	long			start_simulation;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
	t_fork			*forks;
}				t_table;

/*------------------ DEFINE --------------------*/

# define SUCCESS 0
# define ERROR -1

typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIE,
	END,
}			t_status;

/*-------------------- SRC --------------------*/

/*parsing.c*/
void				parse_input(t_table *table, char **argv);

/*init_table.c*/
void				init_table(t_table *table);

/*start_dinner.c*/
bool				is_all_eat(t_table *table);
void				start_simulation(t_table *table);

/*routine.c*/
void				*philo_routine(void *arg);

/*monitor.c*/
void				*monitor_loop(void *arg);

/*------------------- UTILS --------------------*/

/*print.c*/
void				ft_print_status(t_status status, t_philo *philo);

/*utils.c*/
void				ft_error(const char *error);
long				ft_time(t_time time);
void				ft_usleep(long usec, t_table *table);

/*helpers.c*/
void				lock_or_exit(pthread_mutex_t *mtx);
void				unlock_or_exit(pthread_mutex_t *mtx);

#endif