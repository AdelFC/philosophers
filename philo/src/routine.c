/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:20:41 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/27 14:27:36 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* routine
 * Objectif :
 *   - Représenter la routine de vie d’un philosophe :
 *       - Prendre les fourchettes, manger, dormir, penser.
 *       - Mettre à jour les compteurs et le temps du dernier repas.
 *       - Signaler quand il a atteint son quota de repas.
 * Sortie :
 *   - Fonction de thread qui boucle tant que la simulation est active.
 *   - Retourne NULL à la fin de la simulation.
 */
static void	philo_take_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	lock_or_exit(&philo->right_fork->fork);
	ft_print_status(TAKE_FIRST_FORK, philo);
	lock_or_exit(&philo->left_fork->fork);
	ft_print_status(TAKE_SECOND_FORK, philo);
}

static void	philo_eat_sleep_think(t_philo *philo)
{
	int	time_to_think;

	philo_take_forks(philo);
	lock_or_exit(&philo->philo_mtx);
	philo->last_meal_time = ft_time(MILLISECOND);
	philo->meals_counter++;
	if (philo->table->nbr_max_meals > 0
		&& philo->meals_counter == philo->table->nbr_max_meals)
		philo->full = 1;
	unlock_or_exit(&philo->philo_mtx);
	ft_print_status(EAT, philo);
	ft_usleep(philo->table->time_to_eat * 1000, philo->table);
	unlock_or_exit(&philo->left_fork->fork);
	unlock_or_exit(&philo->right_fork->fork);
	ft_print_status(SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep * 1000, philo->table);
	ft_print_status(THINK, philo);
	time_to_think = philo->table->time_to_die - philo->table->time_to_eat
		- philo->table->time_to_sleep - 100;
	if (time_to_think < 0)
		time_to_think = 1;
	ft_usleep(time_to_think * 1000, philo->table);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo->table);
	if (philo->philo_id % 2 == 0)
	{
		ft_print_status(THINK, philo);
		ft_usleep((philo->table->time_to_eat / 2) * 1000, philo->table);
	}
	while (!get_end_simulation(philo->table))
		philo_eat_sleep_think(philo);
	return (NULL);
}
