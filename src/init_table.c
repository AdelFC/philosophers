/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:51:04 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/15 20:36:54 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_mutexes(t_fork *forks, int philo_nbr)
{
	int	i;

	i = 0;
	while (i < philo_nbr)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
			ft_error("Error: mutex init");
		forks[i].fork_id= i;
		i++;
	}
}
static void assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->right_fork  = &forks[(i + 1) % philo_nbr];
	philo->left_fork = &forks[i];
	if (philo->philo_id % 2 != 0)
	{
		philo->right_fork = &forks[i];
		philo->left_fork  = &forks[(i + 1) % philo_nbr];
	}
}

static void init_philos(t_table *table)
{
	int i; 
	t_philo *philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->full = 0;
		philo->meals_counter = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->philo_mtx, NULL) != 0)
			ft_error("Error: mutex init");
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	init_table(t_table *table)
{
	table->end_simulation = 0;
	table->all_threads_ready = 0;
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		ft_error("Error: mutex init");
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		ft_error("Error: mutex init");
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		ft_error("Error: malloc");
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		ft_error("Error: malloc");
	init_mutexes(table->forks, table->philo_nbr);
	init_philos(table);
}
