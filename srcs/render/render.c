/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:19:52 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/19 14:20:01 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_bool	check_mat_ptr(t_obj *obj, t_mat *mat_ptr)
{
	if (obj->type & SP)
		return (((t_sp*)(obj->obj))->mat_ptr == mat_ptr);
	if (obj->type & PL)
		return (((t_pl*)(obj->obj))->mat_ptr == mat_ptr);
	if (obj->type & SQ)
		return (((t_sq*)(obj->obj))->mat_ptr == mat_ptr);
	if (obj->type & CY)
		return (((t_cy*)(obj->obj))->mat_ptr == mat_ptr);
	if (obj->type & TR)
		return (((t_tr*)(obj->obj))->mat_ptr == mat_ptr);
	else
		return (0);
}

float	hit_light(t_obj *objs, t_hit *hit, t_hit_rec *l_rec, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_obj		*tmp;
	t_bool		ret;

	ret = FALSE;
	if (!(tmp = objs))
		return (FALSE);
	while (tmp)
	{
		if (!check_mat_ptr(tmp, rec->mat_ptr))
		{
			if (check_hit(tmp, hit, &tmp_rec))
			{
				if (tmp_rec.t < hit->t_max)
				{
					ret = TRUE;
					hit->t_max = tmp_rec.t;
					*l_rec = tmp_rec;
				}
			}
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_vec	*get_light_at(t_vec *color, t_conf *conf, t_light *light,
												t_hit_rec *rec)
{
	float		dot;
	t_vec		tmp_v;
	t_hit		hit;
	t_hit_rec	l_rec;

	hit.t_min = 0.0001;
	while (light)
	{
		hit.t_max = v_len(v_sub(&tmp_v, &rec->p, &light->pos));
		hit.ray.pos = light->pos;
		v_unit(&hit.ray.dir, &tmp_v);
		dot = v_dot(&rec->normal, v_mul(&tmp_v, &hit.ray.dir, -1));
		if (!hit_light(conf->objs, &hit, &l_rec, rec))
		{
			if (dot > 0)
			{
				v_mul(&tmp_v, &light->rgb, light->ratio * dot);
				v_add(color, color, v_prod(&tmp_v, &tmp_v,
										&rec->mat_ptr->attenuation));
			}
		}
		light = light->next;
	}
	return (color);
}

t_vec	*pixel_color(t_vec *color, t_ray ray, t_conf *conf)
{
	t_hit		hit;
	t_hit_rec	rec;
	t_light		*light;

	hit.t_min = 0.0001;
	hit.t_max = FLT_MAX;
	hit.ray = ray;
	new_vec(color, 0, 0, 0);
	if (hit_any(conf->objs, &hit, &rec))
	{
		v_prod(color, &rec.mat_ptr->attenuation,
					v_mul(color, &conf->amb_l->rgb, conf->amb_l->ratio));
		light = conf->lights;
		get_light_at(color, conf, light, &rec);
		color->x = color->x > 1 ? 1 : color->x;
		color->y = color->y > 1 ? 1 : color->y;
		color->z = color->z > 1 ? 1 : color->z;
	}
	return (color);
}

void	render(t_conf *conf)
{
	t_ray	ray;
	t_vec	color;
	int		i;
	t_coord	coord;

	coord.y = conf->res->y;
	while (coord.y)
	{
		coord.x = 0;
		while (coord.x < conf->res->x)
		{
			get_ray(&ray, conf->cam, (float)(coord.x) / (float)(conf->res->x),
									(float)(coord.y) / (float)(conf->res->y));
			pixel_color(&color, ray, conf);
			i = coord.x++ * (conf->cam->bpp / 8) +
				(conf->res->y - coord.y) * conf->cam->line;
			v_mul(&color, &color, 255);
			conf->cam->data[i] = color.z;
			conf->cam->data[i + 1] = color.y;
			conf->cam->data[i + 2] = color.x;
			conf->cam->data[i + 3] = 0;
		}
		--coord.y;
	}
}
