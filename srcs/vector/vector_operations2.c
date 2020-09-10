/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:38:03 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:52:47 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	*v_unit(t_vec *dest, t_vec *v1)
{
 	float	len;

	len = v_len(v1);
	new_vec(dest, v1->x / len, v1->y / len, v1->z / len);
	return (dest);
}

t_vec	*v_cross(t_vec *dest, t_vec *v1, t_vec *v2)
{
	dest->x = v1->y * v2->z - v1->z * v2->y;
	dest->y = v1->z * v2->x - v1->x * v2->z;
	dest->z = v1->x * v2->y - v1->y * v2->x;
	return (dest);
}

float	v_dot(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

float	v_sqr_len(t_vec *v)
{
	return ((float)v->x * v->x + v->y * v->y + v->z * v->z);
}

t_vec	*v_prod(t_vec *dest, t_vec *v1, t_vec *v2)
{
	return (new_vec(dest, v1->x * v2->x, v1->y * v2->y, v1->z * v2->z));
}
