/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 13:29:42 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:39:16 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool		hit_plane(t_plane *pl, t_hit *hit, t_hit_rec *rec)
{
	t_vec	normal;
	t_vec	tmp;
	float	t;
	float	dv;

	v_unit(&normal, &pl->dir);
	t = v_dot(&normal, &hit->ray.dir);
	(void)dv;
	(void)tmp;
	(void)rec;
/*	if (dv == 0)
//			return (FALSE);
	t = (v_dot(&normal, v_sub(&tmp, &hit->ray.pos, &pl->pos)));
	if (t < 0)
			return (FALSE);
	if (rec)
	{
		v_add(&rec->p, &hit->ray.pos, &hit->ray.dir);
		if (dv < 0)
			rec->normal = normal;
		else
			v_mul(&rec->normal, &normal, -1);
		rec->mat_ptr = pl->mat_ptr;
	}*/
	return (TRUE);
}
