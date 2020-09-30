/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:41:49 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/30 18:21:01 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	get_t(float t1, float t2)
{
	float		min;

	min = 0.001;
	if (t1 <= min && t2 <= min)
		return (0);
	if (t1 <= min)
		return (t2);
	if (t2 <= min)
		return (t1);
	return (t1 < t2 ? t1 : t2);
}

/*
**t_vec	*cy_get_normal(t_cy *cy, t_hit_rec *rec)
**{
**	float		t;
**	t_hit		hit_c;
**
**	hit_c.t_min = 0.000001;
**	hit_c.t_max = FLT_MAX;
**	hit_c.ray.pos = rec->p;
**	v_unit(&hit_c.ray.pos, &cy->ori);
**	if ((t = inter_plane(&hit_c, &cy->pos, &cy->ori)) != FLT_MAX)
**		return (v_unit(&rec->normal, v_sub(&rec->normal, &rec->p, v_add(
**			&rec->normal, &cy->pos, v_mul(&rec->normal, &cy->ori, t * -1)))));
**	v_mul(&hit_c.ray.dir, &hit_c.ray.dir, -1);
**	t = inter_plane(&hit_c, &cy->pos, &cy->ori);
**	return (v_unit(&rec->normal, v_sub(&rec->normal, &rec->p, v_add(
**		&rec->normal, &cy->pos, v_mul(&rec->normal, &cy->ori, t)))));
**}
*/

t_vec	*cy_get_normal(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	float		m;
	t_vec		unit_v;
	t_vec		tmp_v;

	v_unit(&unit_v, &cy->ori);
	m = (v_dot(&hit->ray.dir, &unit_v) * rec->t)
		+ v_dot(v_sub(&tmp_v, &hit->ray.pos, &cy->pos), &unit_v);
	v_sub(&rec->normal, &rec->p, &cy->pos);
	v_sub(&rec->normal, &rec->normal, v_mul(&unit_v, &unit_v, m));
	return (v_unit(&rec->normal, &rec->normal));
}

float	inter_disk(t_cy *cy, t_hit *hit, t_vec *position, t_vec *orientation)
{
	float		t;
	t_vec		tmp_v;
	t_vec		p;

	if (!(t = inter_plane(hit, position, orientation)))
		return (FALSE);
	pt_at_param(&p, &hit->ray, t);
	v_sub(&tmp_v, &p, position);
	if (sqrt(v_dot(&tmp_v, &tmp_v)) <= cy->diam / 2)
		return (t);
	return (0);
}

t_bool	cy_check_caps(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_hit		hit_c;
	float		t1;
	float		t2;
	t_vec		tmp_v;

	hit_c.t_min = 0.00001;
	hit_c.t_max = cy->height / 2;
	hit_c.ray.pos = cy->pos;
	v_unit(&hit_c.ray.dir, &cy->ori);
	t1 = inter_plane(&hit_c, &rec->p, &cy->ori);
	hit_c.t_max = cy->height / 2;
	v_mul(&hit_c.ray.dir, &hit_c.ray.dir, -1);
	if (!t1 && !(t2 = inter_plane(&hit_c, &rec->p, &cy->ori)))
	{
		t1 = inter_disk(cy, hit, v_add(&tmp_v, &cy->pos,
			v_mul(&tmp_v, v_unit(&tmp_v, &cy->ori), cy->height / 2)), &cy->ori);
		t2 = inter_disk(cy, hit, v_add(&tmp_v, &cy->pos, v_mul(&tmp_v,
						v_unit(&tmp_v, &cy->ori), cy->height / -2)), &cy->ori);
		if (!(rec->t = get_t(t1, t2)))
			return (FALSE);
		pt_at_param(&rec->p, &hit->ray, rec->t);
		v_unit(&rec->normal, v_mul(&rec->normal, &cy->ori,
										rec->t == t1 ? 1 : -1));
	}
	return (TRUE);
}

t_bool	hit_cylinder(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_quad_eq	eq;
	t_vec		cross;
	t_vec		cross2;
	t_vec		tmp_v;
	float		t;

	v_cross(&cross, &hit->ray.dir, &cy->ori);
	v_sub(&tmp_v, &hit->ray.pos, &cy->pos);
	eq.a = v_dot(&cross, &cross);
	eq.b = 2 * (v_dot(&cross, v_cross(&cross2, &tmp_v, &cy->ori)));
	eq.c = v_dot(&cross2, &cross2) - (pow(cy->diam / 2, 2) *
		v_dot(&cy->ori, &cy->ori));
	if ((eq.delta = (eq.b * eq.b) - (4 * eq.a * eq.c)) < 0)
		return (FALSE);
	eq.delta = sqrt(eq.delta);
	eq.a *= 2;
	if ((t = get_t((-eq.b + eq.delta) / (eq.a),
	(-eq.b - eq.delta) / (eq.a))) <= 0 || t <= hit->t_min || t >= hit->t_max)
		return (FALSE);
	rec->t = t;
	pt_at_param(&rec->p, &hit->ray, rec->t);
	rec->mat_ptr = cy->mat_ptr;
	cy_get_normal(cy, hit, rec);
	return (cy_check_caps(cy, hit, rec));
}

/*
**	float		tmp;
**	tmp = (v_dot(&hit->ray.dir, &unit_v) * rec->t) + v_dot(&tmp_v, &unit_v);
**	v_sub(&rec->normal, &cy->pos, v_mul(&unit_v, &unit_v, tmp));
**	v_sub(&rec->normal, &rec->p, &rec->normal);
**	v_unit(&rec->normal, &rec->normal);
*/
