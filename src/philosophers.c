/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:47:41 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/15 20:28:20 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_table table;

    if (argc < 5 || argc > 6)
    {
        ft_error("Error: Incorrect input");
    }
    parse_input(&table, argv);
    init_table(&table);
    if (!table.philos || !table.forks)
	    ft_error("Error: malloc failure");
    dinner_start(&table);
    free(table.forks);
    free(table.philos);
    return (SUCCESS);
}
