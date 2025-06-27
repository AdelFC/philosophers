/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:21:38 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/22 23:31:09 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result < 0)
			ft_error("Error: negative result");
		i++;
	}
	return (result * sign);
}

/* valid_argv
* Objectif :
*   - Vérifier qu’une chaîne n’est pas vide, 
* ne contient que des chiffres (optionnellement précédés d’un '+').
*   - Limiter la taille maximale à 10 chiffres.
* Sortie :
*   - Retourne la chaîne si elle est valide.
*   - Termine le programme sinon.
*/
static const char	*valid_argv(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		ft_error("Error: empty argument");
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		ft_error("Error: '+' must be followed by digits");
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			ft_error("Error: argument must be numeric and positive");
		i++;
	}
	if (i > 10)
		ft_error("Error: argument too large");
	return (str);
}

/* parse_input
* Objectif :
*   - Vérifier et parser les arguments du programme.
*   - Initialiser les champs principaux de t_table à partir des arguments.
*   - Gérer les limites sur le nombre de philosophes et les timings.
* Sortie :
*   - Remplit philo_nbr,time_to_die,time_to_eat,time_to_sleep,nbr_max_meals.
*   - Termine le programme si un argument est invalide ou hors limites.
*/
void	parse_input(t_table *table, char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && i <= 5)
	{
		valid_argv(argv[i]);
		i++;
	}
	table->philo_nbr = ft_atoi(argv[1]);
	if (table->philo_nbr < 1 || table->philo_nbr > 200)
		ft_error("Error: number_of_philosophers must be between 1 and 200");
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		ft_error("Error: time values must be at least 60 ms");
	if (argv[5])
		table->nbr_max_meals = ft_atoi(argv[5]);
	else
		table->nbr_max_meals = -1;
}
