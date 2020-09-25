/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:02:49 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/24 08:48:36 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool		hit_square(t_sq *sq, t_hit *hit, t_hit_rec *rec)
{
	float	t1;
	float	t2;
	float	tmp;
	t_vec	tmp_vec;

	if (!(t1 = inter_plane(hit, &sq->pos, &sq->ori)))
		return (FALSE);
	v_add(&tmp_vec, v_mul(&tmp_vec, &hit->ray.dir, t1), &hit->ray.pos);
	v_sub(&tmp_vec, &tmp_vec, &sq->pos);
	tmp_vec.x *= tmp_vec.x < 0 ? -1 : 1;
	tmp_vec.y *= tmp_vec.y < 0 ? -1 : 1;
	tmp_vec.z *= tmp_vec.z < 0 ? -1 : 1;
	if ((tmp_vec.x > (t2 = sq->size / 2)) || tmp_vec.y > t2 || tmp_vec.z > t2)
		return (FALSE);
	rec->t = t1;
	pt_at_param(&rec->p, &hit->ray, rec->t);
	rec->mat_ptr = sq->mat_ptr;
	tmp = v_dot(&hit->ray.dir, &sq->ori);
	v_mul(&rec->normal, &sq->ori, tmp >= 0 ? -1 : 1);
	v_unit(&rec->normal, &rec->normal);
	return (TRUE);
}
