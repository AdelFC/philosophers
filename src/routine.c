/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:20:41 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/13 18:54:40 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_eat(t_philo *philo)
{
    int val;

    val = pthread_mutex_lock(&philo->left_fork->fork);
    if (val != 0)
        ft_error("Impossible de verrouiller la première fourchette");
    ft_print_status(TAKE_FIRST_FORK, philo);
    val = pthread_mutex_lock(&philo->right_fork->fork);
    if (val != 0)
        ft_error("Impossible de verrouiller la deuxième fourchette");
    ft_print_status(TAKE_SECOND_FORK, philo);
    val = pthread_mutex_lock(&philo->philo_mtx);
    if (val != 0)
        ft_error("Impossible de verrouiller le mutex du philosophe");
    philo->last_meal_time = ft_time(MILLISECOND);
    philo->meals_counter++;
    val = pthread_mutex_unlock(&philo->philo_mtx);
    if (val != 0)
        ft_error("Impossible de déverrouiller le mutex du philosophe");
    ft_print_status(EAT, philo);
    ft_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->nbr_max_meals > 0
        && philo->meals_counter == philo->table->nbr_max_meals)
    {
        val = pthread_mutex_lock(&philo->philo_mtx);
        if (val != 0)
            ft_error("Impossible de verrouiller le mutex du philosophe");
        philo->full = 1;
        val = pthread_mutex_unlock(&philo->philo_mtx);
        if (val != 0)
            ft_error("Impossible de déverrouiller le mutex du philosophe");
    }
    val = pthread_mutex_unlock(&philo->left_fork->fork);
    if (val != 0)
        ft_error("Impossible de déverrouiller la première fourchette");
    val = pthread_mutex_unlock(&philo->right_fork->fork);
    if (val != 0)
        ft_error("Impossible de déverrouiller la deuxième fourchette");
}

void ft_think(t_philo *philo)
{
    ft_print_status(THINK, philo);
}
