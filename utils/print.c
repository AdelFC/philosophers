/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:00:22 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/22 23:45:04 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_print_status
* Objectif :
*   - Afficher l’état courant d’un philosophe 
* (prise de fourchette, manger, dormir, penser, mort) avec timestamp.
*   - Ne rien afficher après la fin de la simulation.
* Sortie :
*   - Affiche le message d’état formaté sur la sortie standard.
*   - Retourne sans rien faire si la simulation est terminée.
*/
void	ft_print_status(t_status status, t_philo *philo)
{
	long	time;

	if (pthread_mutex_lock(&philo->table->print_lock) != 0)
		ft_error("Unable to lock print_lock");
	if (philo->table->end_simulation == 1 && status != END)
	{
		if (pthread_mutex_unlock(&philo->table->print_lock) != 0)
			ft_error("Unable to unlock print_lock");
		return ;
	}
	time = ft_time(MILLISECOND) - philo->table->start_simulation;
	if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		printf("🍴 %ld %d has taken a fork!\n", time, philo->philo_id);
	else if (status == EAT)
		printf("🍝​​ %ld %d is eating!\n", time, philo->philo_id);
	else if (status == SLEEP)
		printf("😴 %ld %d is sleeping...\n", time, philo->philo_id);
	else if (status == THINK)
		printf("💭 %ld %d is thinking...\n", time, philo->philo_id);
	else if (status == DIE)
		printf("💀 %ld %d died!\n", time, philo->philo_id);
	if (pthread_mutex_unlock(&philo->table->print_lock) != 0)
		ft_error("Unable to unlock print_lock");
}

// void	ft_print_status(t_status status, t_philo *philo)
// {
//   int		val;
//   long	time;

//   val = pthread_mutex_lock(&philo->table->print_lock);
//   if (val != 0)
//	 ft_error("Unable to lock print_lock");
//   if (philo->table->end_simulation == 1 && status != END)
//   {
//	 val = pthread_mutex_unlock(&philo->table->print_lock);
//	 if (val != 0)
//	   ft_error("Unable to unlock print_lock");
//	 return ;
//   }
//   time = ft_time(MILLISECOND) - philo->table->start_simulation;
//   if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
//	 printf("%ld %d has taken a fork\n", time, philo->philo_id);
//   else if (status == EAT)
//	 printf("%ld %d is eating\n", time, philo->philo_id);
//   else if (status == SLEEP)
//	 printf("%ld %d is sleeping\n", time, philo->philo_id);
//   else if (status == THINK)
//	 printf("%ld %d is thinking\n", time, philo->philo_id);
//   else if (status == DIE)
//	 printf("%ld Simulation ended\n", time);
//   val = pthread_mutex_unlock(&philo->table->print_lock);
//   if (val != 0)
//	 ft_error("Unable to unlock print_lock");
// }
