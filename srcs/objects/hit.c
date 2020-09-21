/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 11:44:07 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/21 09:35:53 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool		check_hit(t_obj *objs, t_hit *hit, t_hit_rec *rec)
{
	if (objs->type & SP)
		return (hit_sphere(objs->obj, hit, rec));
	if (objs->type & PL)
		return (hit_plane(objs->obj, hit, rec));
	if (objs->type & SQ)
		return (hit_square(objs->obj, hit, rec));
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
	while (tmp)
	{
		if (check_hit(tmp, hit, &tmp_rec))
		{
			ret = TRUE;
			hit->t_max = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (ret);
}
