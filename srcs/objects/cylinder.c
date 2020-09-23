/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:41:49 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/23 13:09:36 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool		cy_check_t(t_cy *cy, t_hit *hit, t_hit_rec *rec, t_quad_eq eq)
{
	float		t1;
	float		t2;

	if ((t1 = (-eq.b - eq.delta) / eq.a))
		rec->t = t1;
	if ((t2 = (-eq.b + eq.delta) / eq.a))
		rec->t = t2;
	return (TRUE);
}

t_bool		hit_cylinder(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_quad_eq	eq;
	t_vec		cross;
	t_vec		cross1;
	t_vec		tmp_v;

	v_cross(&cross, &hit->ray.dir, &cy->ori);
	v_cross(&cross1, v_sub(&cross1, &hit->ray.pos, &cy->pos), &cy->ori);
	eq.a = v_dot(&cross, &cross);
	eq.b = 2 * v_dot(&cross, &cross1);
	eq.c = v_dot(&cross1, &cross) - (pow(cy->diam / 2 , 2) *
			v_dot(&cy->ori, &cy->ori));
	if ((eq.delta = pow(eq.b, 2) - (4 * eq.a * eq.c)) < 0)
		return (FALSE);
	eq.a = 2 * eq.a;
	s.delta = sqrt(eq.delta);
	return (cy_check_t(cy, hit, rec, eq));
}
