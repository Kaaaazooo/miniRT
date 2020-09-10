/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:12:27 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:50:37 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ray	*new_ray(t_ray *r, t_vec pos, t_vec dir)
{
	r->pos = pos;
	r->dir = dir;
	return (r);
}

t_ray	*get_ray(t_ray *ray, t_cam *cam, float u, float v)
{
	t_vec	tmp1;
	t_vec	tmp2;

	ray->pos = cam->pos;
	v_mul(&tmp1, &cam->ho, u);
	v_mul(&tmp2, &cam->ve, v);
	v_add(&ray->dir, &tmp1, &tmp2);
	v_add(&ray->dir, &ray->dir, &cam->llc);
	v_sub(&ray->dir, &ray->dir, &cam->pos);
	return (ray);
}

t_vec	*pt_at_param(t_vec *dest, t_ray *r, float t)
{
	t_vec	v1;

	v_mul(&v1, &r->dir, t);
	return (v_add(dest, &v1, &r->pos));
}
