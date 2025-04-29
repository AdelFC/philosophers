/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:47:43 by afodil-c          #+#    #+#             */
/*   Updated: 2025/04/29 03:03:54 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*------------------- LIBS --------------------*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

/*------------------- STRUC --------------------*/

/*------------------ DEFINE --------------------*/

# define SUCCESS 0
# define ERROR -1

/*-------------------- SRC --------------------*/

/*philosophers.c*/

/*------------------- UTILS --------------------*/

/*utils.c*/

int utils(void);


#endif