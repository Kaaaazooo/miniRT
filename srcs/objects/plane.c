/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 13:29:42 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/17 11:26:44 by sabrugie         ###   ########.fr       */
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
		return (FALSE);
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
