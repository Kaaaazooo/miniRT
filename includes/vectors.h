/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:31:22 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/24 08:34:44 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "mini_rt.h"

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vec;

t_vec			*new_vec(t_vec *dest, float x, float y, float z);
int				v_rgb(t_vec *col);

t_vec			*v_add(t_vec *dest, t_vec *v1, t_vec *v2);
t_vec			*v_sub(t_vec *dest, t_vec *v1, t_vec *v2);
t_vec			*v_mul(t_vec *dest, t_vec *v1, float m);
t_vec			*v_prod(t_vec *dest, t_vec *v1, t_vec *v2);
t_vec			*v_div(t_vec *dest, t_vec *v1, float m);

t_vec			*v_unit(t_vec *dest, t_vec *v1);
t_vec			*v_cross(t_vec *dest, t_vec *v1, t_vec *v2);
float			v_dot(t_vec *v1, t_vec *v2);
float			v_len(t_vec *v);
float			v_sqr_len(t_vec *v);

#endif
