/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:44:15 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/21 16:02:57 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool		inside_outside(t_tr *tr, t_vec *pos, t_vec *normal)
{
	t_vec		edge;

	v_sub(&edge, tr->point1, tr->point0);
	v_prod(&edge, v_sub(&edge, pos, &tr->point0), &edge);
	if (v_dot(normal, &edge) < 0)
		return (FALSE);
	v_sub(&edge, tr->point2, tr->point1);
	v_prod(&edge, v_sub(&edge, pos, &tr->point0), &edge);
	if (v_dot(normal, &edge) < 0)
		return (FALSE);
	v_sub(&edge, tr->point0, tr->point2);
	v_prod(&edge, v_sub(&edge, pos, &tr->point0), &edge);
	if (v_dot(normal, &edge) < 0)
		return (FALSE);
	return (TRUE);
}

t_bool		hit_triangle(t_tr *tr, t_hit *hit, t_hit_rec *rec)
{
	t_vec		side0;
	t_vec		side1;
	t_vec		normal;
	t_vec		tmp_vec;
	t_quad_eq	eq;

	v_sub(&side0, tr->point1, tr->point0);
	v_sub(&side1, tr->point2, tr->point0);
	v_prod(&normal, &hit->ray.dir, &side1);
	eq.delta = v_dot(&side0, &normal);
	if (fabs(eq.delta) < 0.00001)
		return (FALSE);
	eq.a = 1 / eq.delta;
	eq.b = v_dot(v_sub(&tmp_vec, &hit->ray.pos, &tr->pos), &normal) * eq.a;
	if (eq.b < 0 || eq.b > 1)
		return (FALSE);
	eq.c = v_dot(&hit->ray.dir, v_prod(&tmp_vec, &tmp_vec, &side0)) * eq.a;
	rec->t = v_dot(&side1, &tmp_vec) * eq.a;
	if (eq.c < 0 || eq.b + eq.c > 1 || rec->t <= hit->t_min ||
												rec->t >= hit->t_max)
		return (FALSE);
	rec->mat_ptr = tr->mat_ptr;
	dot = v_dot(&hit->ray.dir, &tmp_vec);
	v_mul(&rec->normal, &normal, dot >= 0 ? -1 : 1);
	v_unit(&rec->normal, &rec->normal);
	return (TRUE);
}

/*
t_bool		hit_triangle(t_tr *tr, t_hit *hit, t_hit_rec *rec)
{
	t_vec		side0;
	t_vec		side1;
	t_vec		pos;
	t_vec		tmp_vec;
	float		dot;

	v_sub(&side0, &tr->point2, &tr->point1);
	v_sub(&side1, &tr->point3, &tr->point1);
	v_prod(&tmp_vec, &side0, &side1);
	dot = v_dot(&tmp_vec, &hit->ray.dir);
	if (fabs(dot) < 0.00001)
		return (FALSE);
	dot = v_dot(&tmp_vec, &tr->point1);
	rec->t = v_dot(&tmp_vec, &hit->ray.pos) + dot;
	if(rec->t <= hit->t_min || rec->t >= hit->t_max)
		return (FALSE);
	pt_at_param(&pos, &hit->ray, rec->t);
	if (!inside_outside(tr, &pos, &tmp_vec))
		return (FALSE);
	rec->mat_ptr = tr->mat_ptr;
	dot = v_dot(&hit->ray.dir, &tmp_vec);
	v_mul(&rec->normal, &normal, dot >= 0 ? -1 : 1);
	v_unit(&rec->normal, &rec->normal);
	return (TRUE);
}
*/
