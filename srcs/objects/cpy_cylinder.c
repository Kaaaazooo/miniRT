/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:41:49 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/25 11:22:07 by sabrugie         ###   ########.fr       */
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

t_bool	cy_check_cap(t_cy *cy, t_hit *hit, t_hit_rec *rec, t_quad_eq *eq)
{
	float		t1;
	float		t2;
	float		t;
	t_hit		hit_cap;
	t_vec		tmp_v;

	t1 = (-eq->b - eq->delta) / eq->a;
	t2 = (-eq->b + eq->delta) / eq->a;
	if ((t = t1 <= t2 ? t1 : t2) <= hit->t_min || t >= hit->t_max)
		return (FALSE);
	hit_cap.t_min = 0.001;
	hit_cap.t_max = FLT_MAX;
	pt_at_param(&hit_cap.ray.pos, &hit->ray, rec->t);
	hit_cap.ray.dir = cy->ori;
	t1 = inter_plane(&hit_cap, &cy->pos, &cy->ori);
	t1 && t1 <= cy->height / 2 ? rec->t = t1 : 0;
	t2 = inter_plane(&hit_cap, &cy->pos, v_mul(&tmp_v, &cy->ori, -1));
	t2 && t2 <= cy->height / 2 ? rec->t = t2 : 0;
	rec->mat_ptr = cy->mat_ptr;
	pt_at_param(&rec->p, &hit->ray, rec->t);
	cy_get_attr(cy, rec);
	return (TRUE);
}

t_bool	hit_cylinder(t_cy *cy, t_hit *hit, t_hit_rec *rec)
{
	t_quad_eq	eq;
	t_vec		cross1;
	t_vec		cross2;

	v_cross(&cross1, &hit->ray.dir, &cy->ori);
	v_cross(&cross2, v_sub(&cross2, &hit->ray.pos, &cy->pos), &cy->ori);
	eq.a = v_dot(&cross1, &cross1);
	eq.b = 2 * v_dot(&cross1, &cross2);
	eq.c = v_dot(&cross2, &cross2) - (pow(cy->diam / 2, 2)) *
		v_dot(&cy->ori, &cy->ori);
	eq.delta = pow(eq.b, 2) - (4 * eq.a * eq.c);
	if (eq.delta < 0)
		return (FALSE);
	eq.a *= 2;
	eq.delta = sqrt(eq.delta);
	return(cy_check_cap(cy, hit, rec, &eq));
}
