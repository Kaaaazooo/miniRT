/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:42:01 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/24 16:44:33 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "mini_rt.h"

typedef char	t_bool;
struct s_configuration;

typedef struct	s_xor
{
	unsigned int a;
}				t_xor;

void			skip_spaces(char **str);
t_vec			skip_atov(char **str, struct s_configuration *conf, char *type);
int				skip_atoi(char **str, struct s_configuration *conf, char *type);
float			skip_atof(char **str, struct s_configuration *conf, char *type);

float			my_rand(t_xor *state);
float			get_t(float t1, float t2);

#endif
