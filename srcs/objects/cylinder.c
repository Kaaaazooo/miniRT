/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:41:49 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/29 16:34:51 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	cy_get_attr(t_cy *cy, t_hit_rec *rec)
{
	t_vec		tmp_v;
	t_hit		hit;
	float		t;

	hit.t_max = FLT_MAX;
	hit.t_min = 0.001;
	if ((t = inter_plane(&hit, &cy->pos, &cy->ori)))
	{
		v_unit(&rec->normal, v_sub(&rec->normal, &hit.ray.pos,
		v_add(&rec->normal, &cy->pos, v_mul(&rec->normal, &cy->ori, t * -1))));
	}
	else
	{
		t = inter_plane(&hit, &cy->pos, v_mul(&tmp_v, &cy->ori, -1));
		v_unit(&rec->normal, v_sub(&rec->normal, &hit.ray.pos,
		v_add(&rec->normal, &cy->pos, v_mul(&rec->normal, &cy->ori, t * -1))));
	}
}

float	inter_disk(t_cy *cy, t_hit *hit, t_vec *position, t_vec *orientation)
{
	float		t;
	t_vec		tmp_v;
	t_vec		p;

	t = inter_plane(hit, position, orientation);
	pt_at_param(&p, &hit->ray, t);
	v_sub(&tmp_v, &p, position);
	if (sqrt(v_dot(&tmp_v, &tmp_v)) <= cy->diam / 2)
		return (t);
	return (FALSE);
}

t_bool	cy_check_caps(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_hit		hit_c;
	float		t1;
	float		t2;
	t_vec		tmp_v;
	t_vec		tmp_ori;

	hit_c.t_max = cy->height / 2;
	hit_c.t_min = 0.001;
	hit_c.ray.pos = cy->pos;
	v_unit(&hit_c.ray.dir, &cy->ori);
	t1 = inter_plane(&hit_c, &rec->p, &cy->ori);
	v_mul(&hit_c.ray.dir, &hit_c.ray.dir, -1);
	hit_c.t_max = cy->height / 2;
	if (!t1 && !(t2 = inter_plane(&hit_c, &rec->p, &cy->ori)))
	{
		t1 = inter_disk(cy, hit, v_add(&tmp_v, &cy->pos, v_mul(&tmp_v, &cy->ori,
					cy->height / 2)), &cy->ori);
		if (!t1 && !(t2 = inter_disk(cy, hit, v_mul(&tmp_v, &tmp_v, -1),
					v_mul(&tmp_ori, &cy->ori, -1))))
			return (FALSE);
		rec->t = (t1 && t1 < t2) || (t1 && !t2) ? t1 : t2;
		pt_at_param(&rec->p, &hit->ray, rec->t);
		v_mul(&rec->normal, &cy->ori, rec->t == t1 ? 1 : -1);
	}
	return (TRUE);
}

float	get_t(t_quad_eq eq)
{
	float	t1;
	float	t2;
	float	sqrt_delta;

	sqrt_delta = sqrt(eq.delta);
	t1 = (-eq.b + sqrt_delta) / (2 * eq.a);
	t2 = (-eq.b - sqrt_delta) / (2 * eq.a);
	if (t1 < 0 && t2 < 0)
		return (0);
	if (t1 < 0)
		return (t2);
	if (t2 < 0)
		return (t1);
	return (t1 < t2 ? t1 : t2);
}

t_bool	hit_cylinder(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_quad_eq	eq;
	t_vec		tmp_v;
	float		tmp;
	t_vec		unit_v;

	eq.a = v_dot(&hit->ray.dir, &hit->ray.dir) -
		(pow(v_dot(&hit->ray.dir, v_unit(&unit_v, &cy->ori)), 2));
	eq.b = 2 * (v_dot(&hit->ray.dir, v_sub(&tmp_v, &hit->ray.pos, &cy->pos)) -
			(v_dot(&hit->ray.dir, &unit_v) * v_dot(&unit_v, &tmp_v)));
	eq.c = v_dot(&tmp_v, &tmp_v) -
			pow(v_dot(&tmp_v, &unit_v), 2) -
			(pow(cy->diam / 2, 2));
	if ((eq.delta = (eq.b * eq.b) - (4 * eq.a * eq.c)) < 0)
		return (FALSE);
	if ((rec->t = get_t(eq)) <= 0)
		return (FALSE);
	pt_at_param(&rec->p, &hit->ray, rec->t);
	rec->mat_ptr = cy->mat_ptr;
	tmp = v_dot(&hit->ray.dir, &unit_v) * rec->t + v_dot(&tmp_v, &unit_v);
	v_sub(&rec->normal, &cy->pos, v_mul(&unit_v, &unit_v, tmp));
	v_sub(&rec->normal, &rec->p, &rec->normal);
	v_unit(&rec->normal, &rec->normal);
	return (cy_check_caps(cy, hit, rec));
}
