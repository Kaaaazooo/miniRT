/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 11:44:07 by sabrugie          #+#    #+#             */
/*   Updated: 2020/02/25 17:24:24 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool		check_hit(t_obj *objs, t_hit *hit, t_hit_rec *rec)
{
	if (objs->type & SP)
		return (hit_sphere(objs->obj, hit, rec));
	if (objs->type & PL)
		return (0);
	if (objs->type & SQ)
		return (0);
	if (objs->type & CY)
		return (0);
	if (objs->type & TR)
		return (0);
	else
		return (0);
}

t_bool		hit_any(t_obj *objs, t_hit *hit, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_obj		*tmp;
	t_bool		ret;

	ret = FALSE;
	if (!(tmp = objs))
		return (FALSE);
	while (objs)
	{
		if (check_hit(objs, hit, &tmp_rec))
		{
			ret = TRUE;
			hit->t_max = tmp_rec.t;
			*rec = tmp_rec;
		}
		objs = objs->next;
	}
	objs = tmp;
	return (ret);
}
