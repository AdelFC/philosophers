/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:21:38 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/13 19:03:45 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int ft_atoi(const char *str)
{
    int i;
    int result;
    int sign;

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
    while (str[i] >= 48 && str[i] <= 57)
    {
        result = result * 10 + (str[i] - 48);
		if (result < 0)
			ft_error("Error: negative result");
        i++;
    }
    return (result * sign);
}

static const char *valid_argv(const char *str)
{
    int i;

    i = 0;
    if (!str || str[i] == '\0')
        ft_error("Error: empty argument");
    if (str[i] == '+')
        i++;
    if (str[i] == '\0')
        ft_error("Error: '+' must be followed by digits");
    while (str[i] != '\0')
    {
        if (str[i] < 48 || str[i] > 57)
            ft_error("Error: argument must be numeric and positive");
        i++;
    }
    if (i > 10)
        ft_error("Error: argument too large");
    return (str);
}

void parse_input(t_table *table, char **argv)
{
	int i;
	
	i = 1;
	while (argv[i] && i <= 5)
	{
		valid_argv(argv[i]);
		i++;
	}
    table->philo_nbr    = ft_atoi(argv[1]);
    table->time_to_die  = ft_atoi(argv[2]);
    table->time_to_eat  = ft_atoi(argv[3]);
    table->time_to_sleep= ft_atoi(argv[4]);
    if (table->time_to_die < 60 || table->time_to_eat < 60
    	|| table->time_to_sleep < 60)
        ft_error("Error: min 60ms");
    if (argv[5])
        table->nbr_max_meals = ft_atoi(argv[5]);
    else
        table->nbr_max_meals = -1;
}
