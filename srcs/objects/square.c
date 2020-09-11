/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:02:49 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/11 14:09:52 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	calculate_rot(t_vec *c2, t_vec *c3, t_vec rot, t_vec to)
{
	t_vec	c1;
	t_vec	v;
	float	c;
	float	s;
	float	r;

	v_cross(&v, &to, &rot);
	c = v_dot(&rot, &to);
	s = v_sqr_len(&v);
	r = ((1 - c) / s);
	new_vec(&c1, -r * (pow(v.y, 2) + pow(v.z, 2)) + 1, r * v.x * \
				v.y - v.z, r * v.x * v.z + v.y);
	new_vec(c2, r * v.x * v.y + v.z, -r * (pow(v.x, 2) + \
			pow(v.z, 2)) + 1, r * v.y * v.x - v.x);
	new_vec(c3, r * v.x * v.z - v.y, r * v.y * v.z - v.x, -r * \
					(pow(v.x, 2) + pow(v.y, 2)) + 1);
	return (c1);
}

t_vec	apply_rot(t_vec pos, t_vec dir, t_vec rot)
{
	t_vec	c1;
	t_vec	c2;
	t_vec	c3;
	t_vec	prev;

	if (dir.x == 0 && dir.y < 0 && dir.z == 0)
		new_vec(&pos, pos.x, pos.y, -pos.z);
	else if (!(dir.x == 0 && dir.y != 0 && dir.z == 0))
	{
		prev = pos;
		c1 = calculate_rot(&c2, &c3, rot, dir);
		new_vec(&pos, v_dot(&c1, &prev), v_dot(&c2, &prev), v_dot(&c3, &prev));
	}
	return (pos);
}

float		inter_plane(t_hit *hit, t_sq *square)
{
	float	a;
	float	b;
	float	t;
	t_vec	tmp_vec;

	v_sub(&tmp_vec, &hit->ray.pos, &square->pos);
	a = v_dot(&tmp_vec, &square->ori);
	b = v_dot(&hit->ray.dir, &square->ori);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t = -a / b;
	if (t <= hit->t_min || t >= hit->t_max)
		return (0);
	return (t);
}

t_bool		hit_square(t_sq *sq, t_hit *hit, t_hit_rec *rec)
{
	float	t;
	float	a;
	float	tmp;
	t_vec	p;
	t_vec	tmp_vec;

	if (!(t = inter_plane(hit, sq)))
		return (FALSE);
	v_mul(&tmp_vec, &hit->ray.dir, t);
	v_add(&p, &hit->ray.pos, &tmp_vec);
	if (sq->ori.x != 0 || sq->ori.y == 0 \
		|| sq->ori.z != 0)
		p = apply_rot(p, sq->ori, *new_vec(&tmp_vec, 0, 1, 0));
	a = sq->pos.x - sq->size / 2;
	tmp_vec.x = sq->pos.x + sq->size / 2;
	tmp_vec.y = sq->pos.z - sq->size / 2;
	tmp_vec.z = sq->pos.z + sq->size / 2;
	if (!((p.x >= a && p.x <= tmp_vec.x) && \
		(p.z <= tmp_vec.z && p.z >= tmp_vec.y)))
		return (FALSE);
	rec->t = t;
	rec->p = p;
	rec->mat_ptr = sq->mat_ptr;
	tmp = v_dot(&hit->ray.dir, &sq->ori);
	rec->normal = sq->ori;
	if (tmp >= 0)
		v_mul(&rec->normal, &sq->ori, -1);
	return (TRUE);
}
