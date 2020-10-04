/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 13:29:42 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/04 13:36:46 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool		hit_plane(t_pl *pl, t_hit *hit, t_hit_rec *rec)
{
	t_vec	tmp_vec;
	float	tmp;
	float	a;
	float	b;
	float	t;

	v_sub(&tmp_vec, &hit->ray.pos, &pl->pos);
	a = v_dot(&tmp_vec, &pl->ori);
	b = v_dot(&hit->ray.dir, &pl->ori);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
	{
		printf("ray_pos[%f, %f, %f] - pl->pos[%f, %f, %f] = [%f, %f, %f]\n",
			hit->ray.pos.x, hit->ray.pos.y, hit->ray.pos.z,
			pl->pos.x, pl->pos.y, pl->pos.z,
			tmp_vec.x, tmp_vec.y, tmp_vec.z);
		return (FALSE);
	}
	t = -a / b;
	if (t <= hit->t_min || t >= hit->t_max)
		return (FALSE);
	rec->t = t;
	rec->mat_ptr = pl->mat_ptr;
	pt_at_param(&rec->p, &hit->ray, rec->t);
	rec->normal = pl->ori;
	tmp = v_dot(&hit->ray.dir, &pl->ori);
	if (tmp >= 0)
		v_mul(&rec->normal, &pl->ori, -1);
	v_div(&rec->normal, &rec->normal, v_len(&rec->normal));
	return (TRUE);
}

float		inter_plane(t_hit *hit, t_vec *position, t_vec *orientation)
{
	float	a;
	float	b;
	float	t;
	t_vec	tmp_vec;

	v_sub(&tmp_vec, &hit->ray.pos, position);
	a = v_dot(&tmp_vec, orientation);
	b = v_dot(&hit->ray.dir, orientation);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t = -a / b;
	if (t <= hit->t_min || t >= hit->t_max)
		return (0);
	return (t);
}
