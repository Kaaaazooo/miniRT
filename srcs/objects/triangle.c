/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:44:15 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/22 12:56:30 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool		hit_triangle(t_tr *tr, t_hit *hit, t_hit_rec *rec)
{
	t_vec		side0;
	t_vec		side1;
	t_vec		tmp_vec;
	t_vec		p_vec;
	t_vec		q_vec;

	v_sub(&side0, &tr->point1, &tr->point0);
	v_sub(&side1, &tr->point2, &tr->point0);
	if ((v_dot(&side0, v_cross(&p_vec, &hit->ray.dir, &side1)) > -1e-8) &&
			(v_dot(&side0, &p_vec) < 1e-8))
		return (FALSE);
	if (v_dot(v_sub(&tmp_vec, &hit->ray.pos, &tr->point0), &p_vec) *
		(1 / v_dot(&side0, &p_vec)) < 0 || v_dot(&tmp_vec, &p_vec) *
		(1 / v_dot(&side0, &p_vec)) > 1)
		return (FALSE);
	v_cross(&q_vec, &tmp_vec, &side0);
	if (v_dot(&hit->ray.dir, &q_vec) * (1 / v_dot(&side0, &p_vec)) < 0 ||
		v_dot(&tmp_vec, &p_vec) * (1 / v_dot(&side0, &p_vec)) +
		v_dot(&hit->ray.dir, &q_vec) * (1 / v_dot(&side0, &p_vec)) > 1)
		return (FALSE);
	rec->t = v_dot(&side1, &q_vec) * (1 / v_dot(&side0, &p_vec));
	if (rec->t <= hit->t_min || rec->t >= hit->t_max)
		return (FALSE);
	pt_at_param(&rec->p, &hit->ray, rec->t);
	rec->mat_ptr = tr->mat_ptr;
	if (v_dot(&hit->ray.dir, &tr->ori) >= 0)
		v_unit(&rec->normal, v_mul(&rec->normal, &tr->ori, -1));
	return (TRUE);
}
