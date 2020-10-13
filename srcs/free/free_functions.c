/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:05:58 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 20:31:47 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_objs(t_obj *objs)
{
	t_obj	*tmp;

	while (objs)
	{
		if (objs->type == SP)
			free(((t_sp *)objs->obj)->mat_ptr);
		else if (objs->type == PL)
			free(((t_pl *)objs->obj)->mat_ptr);
		else if (objs->type == SQ)
			free(((t_sq *)objs->obj)->mat_ptr);
		else if (objs->type == CY)
			free(((t_cy *)objs->obj)->mat_ptr);
		else if (objs->type == TR)
			free(((t_tr *)objs->obj)->mat_ptr);
		tmp = objs->next;
		free(objs->obj);
		free(objs);
		objs = tmp;
	}
}

void	free_cams(t_cam *cam)
{
	t_cam	*tmp_cam;

	while (cam)
	{
		if (cam->bpp)
		{
			free(cam->img_ptr);
			free(cam->data);
		}
		tmp_cam = cam->next;
		free(cam);
		cam = tmp_cam;
	}
}

void	free_all(t_conf *conf)
{
	t_light	*tmp_light;

	if (!conf)
		return ;
	free_objs(conf->objs);
	conf->cams = conf->cam;
	free_cams(conf->cams);
	tmp_light = conf->lights;
	while (conf->lights)
	{
		tmp_light = conf->lights->next;
		free(conf->lights);
		conf->lights = tmp_light;
	}
	free(conf->res);
	free(conf->amb_l);
	free(conf->mlx->ptr);
	free(conf->mlx->win);
}
