/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:42:01 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:28:40 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "mini_rt.h"

typedef char	t_bool;

typedef struct	s_xor
{
	unsigned int a;
}				t_xor;

void			skip_spaces(char **str);
t_vec			skip_atov(char **str);
int				skip_atoi(char **str);
float			skip_atof(char **str);

float			my_rand(t_xor *state);

#endif
