/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:41:49 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/25 14:56:49 by sabrugie         ###   ########.fr       */
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

t_bool	cy_check_caps(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_hit		hit_cap;
	float		t1;
	float		t2;
	t_vec		tmp_v;
	t_vec		pos;

	(void)hit;
	hit_cap.t_min = 0.001;
	hit_cap.t_max = cy->height / 2;
	hit_cap.ray.pos = cy->pos;
	v_unit(&hit_cap.ray.dir, &cy->ori);
	if ((t1 = inter_plane(&hit_cap, &rec->p, &cy->ori)))
	{
		//t1 <= cy->height / 2 && t1 < rec->t ? rec->t = t1 : 0;
	//	pt_at_param(&rec->p, &hit_cap.ray, t1);
		if ((t1 = v_len(v_sub(&tmp_v, pt_at_param(&pos, &hit_cap.ray, t1),
			&hit->ray.pos))) < rec->t)
			rec->t = t1;
	}
	hit_cap.t_max = cy->height / 2;
	v_mul(&hit_cap.ray.dir, &hit_cap.ray.dir, -1);
	;
	if ((t2 = inter_plane(&hit_cap, &rec->p, v_mul(&tmp_v, &cy->ori, -1))))
	{
		//t2 <= cy->height / 2 && t2 < rec->t ? rec->t = t2 : 0;
	//	pt_at_param(&rec->p, &hit_cap.ray, t2);
		if ((t2 = v_len(v_sub(&tmp_v, pt_at_param(&pos, &hit_cap.ray, t2),
			&hit->ray.pos))) < rec->t)
			rec->t = t2;
	}
	if (!t1 && !t2)
		return (FALSE);
	printf("t1 = %f | t2 = %f\n", t1, t2);
	return (TRUE);
}

t_bool	hit_cylinder(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_quad_eq	eq;
	t_vec		tmp_v;
	float		tmp;
	t_vec		unit_v;
	float		t1;
	float		t2;

	eq.a = v_dot(&hit->ray.dir, &hit->ray.dir) - pow(v_dot(&hit->ray.dir, 
			v_unit(&unit_v, &cy->ori)), 2);
	eq.b = 2 * (v_dot(&hit->ray.dir, v_sub(&tmp_v, &hit->ray.pos, &cy->pos)) - 
			v_dot(&hit->ray.dir, &unit_v) * v_dot(&unit_v, &tmp_v));
	eq.c = v_dot(&tmp_v, &tmp_v) - pow(v_dot(&tmp_v, &unit_v), 2) -
			pow(cy->diam / 2, 2);
	if ((eq.delta = eq.b * eq.b - 4 * eq.a * eq.c) < 0)
		return (FALSE);
	t1 = (-eq.b - sqrt(eq.delta)) / 2 * eq.a;
	t2 = (-eq.b + sqrt(eq.delta)) / 2 * eq.a;
	rec->t = t1 <= t2 ? t1 : t2;
	pt_at_param(&rec->p, &hit->ray, rec->t);
	rec->mat_ptr = cy->mat_ptr;
	tmp = v_dot(&hit->ray.dir, &unit_v) * rec->t + v_dot(&tmp_v, &unit_v);
	v_unit(&rec->normal, v_mul(&rec->normal, v_sub(&rec->normal, &rec->p,
	&cy->pos), tmp));
	if (cy_check_caps(cy, hit, rec) == FALSE)
		return (FALSE);
	return (TRUE);
}
