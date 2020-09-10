/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 09:44:33 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:43:10 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec		*rand_unit_sp(t_vec *dest, t_xor *seed)
{
	t_vec	tmp;
	t_vec	tmp2;

	new_vec(&tmp, my_rand(seed), my_rand(seed), my_rand(seed));
	v_mul(dest, &tmp, 2);
	new_vec(&tmp2, 1, 1, 1);
	v_sub(dest, &tmp, &tmp2);
	while (v_sqr_len(dest) >= 1)
	{
		new_vec(&tmp, my_rand(seed), my_rand(seed), my_rand(seed));
		v_mul(dest, &tmp, 2);
		new_vec(&tmp, 1, 1, 1);
		v_sub(dest, dest, &tmp);
	}
	return (dest);
}

t_bool		hit_sphere(t_sp *sp, t_hit *hit, t_hit_rec *rec)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	delta;
	float	tmp;
	t_vec	v_tmp;

	v_sub(&oc, &hit->ray.pos, &sp->pos);
	a = v_dot(&hit->ray.dir, &hit->ray.dir);
	b = v_dot(&oc, &hit->ray.dir);
	c = v_dot(&oc, &oc) - (sp->radius * sp->radius);
	delta = b * b - a * c;
	if (delta <= 0)
		return (0);
	tmp = (-b - sqrt(b * b - a * c)) / a;
	if (tmp < hit->t_max && tmp > hit->t_min)
	{
		rec->t = tmp;
		pt_at_param(&rec->p, &hit->ray, rec->t);
		v_sub(&v_tmp, &rec->p, &sp->pos);
		v_div(&rec->normal, &v_tmp, sp->radius);
		rec->mat_ptr = sp->mat_ptr;
		return (1);
	}
	tmp = (-b + sqrt(b * b - a * c)) / a;
	if (tmp < hit->t_max && tmp > hit->t_min)
	{
		rec->t = tmp;
		pt_at_param(&rec->p, &hit->ray, rec->t);
		v_sub(&v_tmp, &rec->p, &sp->pos);
		v_div(&rec->normal, &v_tmp, sp->radius);
		rec->mat_ptr = sp->mat_ptr;
		return (1);
	}
	return (0);
}

t_sp	*new_sphere(t_sp *dest, t_vec *v1, float radius)
{
	dest->pos.x = v1->x;
	dest->pos.y = v1->y;
	dest->pos.z = v1->z;
	dest->radius = radius;
	return (dest);
}
