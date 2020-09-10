/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:30:21 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:39:53 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool	scatter_metal(t_ray *ray_in, t_hit_rec *rec, t_xor *seed)
{
	t_vec	reflected;
	t_vec	tmp;

	reflect(&reflected, v_unit(&tmp, &ray_in->dir), &rec->normal);
	v_mul(&tmp, rand_unit_sp(&tmp, seed), rec->mat_ptr->fuzz);
	v_add(&tmp, &tmp, &reflected);
	new_ray(&rec->mat_ptr->scattered, rec->p, tmp);
	return (TRUE);
}

t_bool	scatter_lambert(t_hit_rec *rec, t_xor *seed)
{
	t_vec	target;
	t_vec	tmp;
	t_vec	tmp2;

	v_add(&tmp2, &rec->p, &rec->normal);
	v_add(&target, &tmp2, rand_unit_sp(&tmp, seed));
	new_ray(&rec->mat_ptr->scattered, rec->p, *v_sub(&tmp2, &target, &rec->p));
	return (TRUE);
}

t_bool	scatter(t_hit_rec *rec, t_xor *seed, t_ray *ray_in)
{
	if (rec->mat_ptr->type & LA)
		return (scatter_lambert(rec, seed));
	else if (rec->mat_ptr->type & ME)
		return (scatter_metal(ray_in, rec, seed));
	return (TRUE);
}
