/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 13:29:42 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 14:40:10 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool		hit_plane(t_pl *pl, t_hit *hit, t_hit_rec *rec)
{
	t_vec	normal;
	t_vec	tmp;
	float	t;
	float	dv;

	v_unit(&normal, &pl->dir);
	t = v_dot(&normal, &hit->ray.dir);
	(void)dv;
	(void)tmp;
	(void)rec;
	return (TRUE);
}
