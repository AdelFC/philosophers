/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:47:43 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/13 21:05:16 by afodil-c         ###   ########.fr       */
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

/*------------------- STRUC --------------------*/

typedef struct s_fork
{
	pthread_mutex_t fork;
	int fork_id;
} t_fork;

typedef struct s_philo
{
	int philo_id;
	long meals_counter;
	int full;
	long last_meal_time;
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_t thread_id;
	pthread_mutex_t philo_mtx;
	t_table *table;
}   t_philo;

typedef struct s_table
{
	long philo_nbr;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nbr_max_meals;
	long start_simulation;
	int end_simulation;
	int all_threads_ready;
	pthread_mutex_t table_mutex;
	pthread_mutex_t print_lock;
	t_fork *forks;
	t_philo *philos;
}   t_table;

/*------------------ DEFINE --------------------*/

# define SUCCESS 0
# define ERROR -1

typedef enum e_time
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}   t_time;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIE,
}	t_status;

/*-------------------- SRC --------------------*/

/*parsing.c*/
void 	parse_input(t_table *table, char **argv);

/*init_table.c*/
void	init_table(t_table *table);

/*start_dinner.c*/
void	dinner_start(t_table *table);

/*synchro_dinner.c*/
void	wait_all_threads(t_table *table);

/*print.c*/
void	ft_print_status(t_status status, t_philo *philo);

/*routine.c*/
void	ft_eat(t_philo *philo);
void	ft_think(t_philo *philo);


/*------------------- UTILS --------------------*/

/*utils.c*/
void	ft_error(const char *error);
long	ft_time(t_time time);
void    ft_usleep(long usec, t_table *table);

#endif