/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 13:29:42 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/11 10:14:02 by sabrugie         ###   ########.fr       */
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

	//printf("in\n");
	v_sub(&tmp_vec, &hit->ray.pos, &pl->pos);
	a = v_dot(&tmp_vec, &pl->ori);
	b = v_dot(&hit->ray.dir, &pl->ori);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
	{
	//	printf("out\n");
		return (FALSE);
	}
	t = -a / b;
//t < hit->t_min || t > hit->t_max
	if (t <= hit->t_min || t >= hit->t_max)
	{
	//	printf("out\n");
		return (FALSE);
	}
	rec->t = t;
	rec->mat_ptr = pl->mat_ptr;
	pt_at_param(&rec->p, &hit->ray, rec->t);
	rec->normal = pl->ori;
	tmp = v_dot(&hit->ray.dir, &pl->ori);
	if (tmp >= 0)
		v_mul(&rec->normal, &pl->ori, -1);
	//printf("out\n");
	return (TRUE);
}
/*
t_bool		hit_plane(t_pl *pl, t_hit *hit, t_hit_rec *rec)
{
	t_vec	normal;
	t_vec	tmp;
	float	t;
	float	dv;

	v_unit(&normal, &pl->ori);
	t = v_dot(&normal, &hit->ray.dir);
	(void)dv;
	(void)tmp;
	(void)rec;
	return (TRUE);
}*/
