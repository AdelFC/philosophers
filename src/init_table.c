/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:51:04 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/23 13:59:45 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* init_mutexes
* Objectif :
*   - Initialiser un mutex pour chaque fourchette.
*   - Assigner un identifiant unique à chaque fourchette.
* Sortie :
*   - Prépare chaque t_fork avec son mutex prêt à l’emploi.
*   - Termine le programme en cas d’erreur d’initialisation.
*/
static void	init_mutexes(t_fork *forks, int philo_nbr)
{
	int	i;

	i = 0;
	while (i < philo_nbr)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
			ft_error("Error: mutex init");
		forks[i].fork_id = i;
		i++;
	}
}

/* assign_forks
* Objectif :
*   - Associer à chaque philosophe ses deux fourchettes (gauche et droite).
*   - Inverser l’ordre de prise pour les philosophes d’ID impair pour
* limiter les risques de deadlock.
* Sortie :
*   - Met à jour les pointeurs left_fork et right_fork dans la structure t_philo.
*/
static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->left_fork = &forks[i];
	philo->right_fork = &forks[(i + 1) % philo_nbr];
	if (philo->philo_id % 2 != 0)
	{
		philo->left_fork = &forks[(i + 1) % philo_nbr];
		philo->right_fork = &forks[i];
	}
}

/* init_philos
* Objectif :
*   - Initialiser chaque philosophe :
*       - Attribuer un ID unique (philo_id).
*       - Réinitialiser ses compteurs (meals_counter, full).
*       - Relier le philosophe à la table centrale (table).
*       - Initialiser un mutex pour protéger ses données critiques.
*       - Assigner les fourchettes nécessaires via assign_forks.
* Sortie :
*   - Prépare chaque t_philo avec toutes ses dépendances.
*   - Termine le programme en cas d’erreur d’initialisation.
*/
static void	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = &table->philos[i];
		philo->philo_id = i + 1;
		philo->meals_counter = 0;
		philo->full = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->philo_mtx, NULL) != 0)
			ft_error("Error: mutex init");
		assign_forks(philo, table->forks, i);
		i++;
	}
}

/* init_table
* Objectif :
*   - Allouer et préparer la structure centrale de la simulation :
*       - Initialiser le flag de contrôle de fin (end_simulation).
*       - Créer le mutex global d’affichage (print_lock).
*       - Allouer les tableaux de philosophes et de fourchettes.
*       - Initialiser tous les mutex nécessaires (fourchettes, philosophes).
* Sortie :
*   - Prépare t_table avec toutes les ressources nécessaires.
*   - Termine le programme en cas d’erreur d’allocation ou d’initialisation.
*/
void	init_table(t_table *table)
{
	table->end_simulation = 0;
	if (pthread_mutex_init(&table->end_mtx, NULL) != 0)
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
