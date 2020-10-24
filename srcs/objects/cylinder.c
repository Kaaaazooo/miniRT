/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:41:49 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/24 17:55:07 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
		return (0);
	pt_at_param(&p, &hit->ray, t);
	v_sub(&tmp_v, &p, position);
	if (sqrt(v_dot(&tmp_v, &tmp_v)) <= (cy->diam / 2))
		return (t);
	return (0);
}

t_bool	hit_base(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	float		t1;
	float		t2;
	t_vec		tmp_v;

	t1 = inter_disk(cy, hit, v_add(&tmp_v, &cy->pos,
		v_mul(&tmp_v, v_unit(&tmp_v, &cy->ori), cy->height / 2)), &cy->ori);
	t2 = inter_disk(cy, hit, v_add(&tmp_v, &cy->pos, v_mul(&tmp_v,
					v_unit(&tmp_v, &cy->ori), cy->height / -2)), &cy->ori);
	if (!(rec->t = get_t(t1, t2)))
		return (FALSE);
	pt_at_param(&rec->p, &hit->ray, rec->t);
	v_unit(&rec->normal, v_mul(&rec->normal, &cy->ori,
										rec->t == t1 ? 1 : -1));
	rec->mat_ptr = cy->mat_ptr;
	return (TRUE);
}

t_bool	cy_check_caps(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_hit		hit_c;
	float		t1;
	float		t2;

	pt_at_param(&rec->p, &hit->ray, rec->t);
	rec->mat_ptr = cy->mat_ptr;
	hit_c.t_min = 0.00001;
	hit_c.t_max = cy->height / 2;
	hit_c.ray.pos = cy->pos;
	v_unit(&hit_c.ray.dir, &cy->ori);
	t1 = inter_plane(&hit_c, &rec->p, &cy->ori);
	hit_c.t_max = cy->height / 2;
	v_mul(&hit_c.ray.dir, &hit_c.ray.dir, -1);
	if (!t1 && !(t2 = inter_plane(&hit_c, &rec->p, &cy->ori)))
		return (hit_base(cy, hit, rec));
	cy_get_normal(cy, hit, rec);
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
	t = v_dot(v_unit(&tmp_v, &tmp_v), &cy->ori);
	if ((t >= 0.99999 && t <= 1.00001) || (t <= -0.99999 && t >= -1.00001))
		return (hit_base(cy, hit, rec));
	v_add(&rec->p, &cy->pos, v_mul(&rec->p, &cy->ori, cy->height * 2));
	if ((t = get_t((-eq.b + eq.delta) / (eq.a),
	(-eq.b - eq.delta) / (eq.a))) <= 0 || t <= hit->t_min || t >= hit->t_max)
		return (FALSE);
	rec->t = t;
	return (cy_check_caps(cy, hit, rec));
}
