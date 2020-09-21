/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:03:34 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/21 10:39:49 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		print_objs(t_conf *config)
{
	t_cam		*cam;
	t_light		*light;
	t_obj		*obj;

	cam = config->cam;
	light = config->lights;
	obj = config->objs;

	printf("\nRESOLUTION :\n");
	printf("[%d, %d]\n", config->res->x, config->res->y);
	printf("\nAMBIENT LIGHT :\n");
	printf("[%f] ; [%f, %f, %f]\n", config->amb_l->ratio,
			config->amb_l->rgb.x, config->amb_l->rgb.y,
			config->amb_l->rgb.z);
	printf("\nCAMERAS :\n");
	while (cam)
	{
		printf("%p :\n", cam);
		printf("[%f, %f, %f] ; [%f, %f, %f] ; [%f, %f, %f] ; [%f]\n",
			cam->pos.x, cam->pos.y, cam->pos.z,
			cam->vec.x, cam->vec.y, cam->vec.z,
			cam->vup.x, cam->vup.y, cam->vup.z,
			cam->fov);
		cam = cam->next;
	}
	printf("\nLIGHTS :\n");
	while (light)
	{
		printf("[%f, %f, %f] ; [%f] ; [%f, %f, %f]\n", light->pos.x, light->pos.y,
			light->pos.z, light->ratio,
			light->rgb.x, light->rgb.y, light->rgb.z);
		light = light->next;
	}
	printf("OBJECTS :\n");
	while (obj)
	{
		if (obj->type == SP)
		{
			printf("SP : [%f, %f, %f] ; [%f] ; ", ((t_sp *)(obj->obj))->pos.x,
			((t_sp *)(obj->obj))->pos.y, ((t_sp *)(obj->obj))->pos.z,
			((t_sp *)(obj->obj))->radius);
			printf("[%f, %f, %f]\n", ((t_sp *)(obj->obj))->mat_ptr->attenuation.x,
				((t_sp *)(obj->obj))->mat_ptr->attenuation.y, ((t_sp *)(obj->obj))->mat_ptr->attenuation.z);
		}
		else if (obj->type == PL)
		{
			printf("PL : [%f, %f, %f] ; [%f, %f, %f] ; ", ((t_pl *)(obj->obj))->pos.x,
			((t_pl *)(obj->obj))->pos.y, ((t_pl *)(obj->obj))->pos.z,
			((t_pl *)(obj->obj))->ori.x, ((t_pl *)(obj->obj))->ori.y, ((t_pl *)(obj->obj))->ori.z);
			printf("[%f, %f, %f]\n", ((t_pl *)(obj->obj))->mat_ptr->attenuation.x,
				((t_pl *)(obj->obj))->mat_ptr->attenuation.y, ((t_pl *)(obj->obj))->mat_ptr->attenuation.z);
		}
		else if (obj->type == SQ)
		{
			printf("SQ : [%f, %f, %f] ; [%f, %f, %f] ; [%f] ; ", ((t_sq *)(obj->obj))->pos.x,
			((t_sq *)(obj->obj))->pos.y, ((t_sq *)(obj->obj))->pos.z,
			((t_sq *)(obj->obj))->ori.x, ((t_sq *)(obj->obj))->ori.y, ((t_sq *)(obj->obj))->ori.z,
			((t_sq *)(obj->obj))->size);
			printf("[%f, %f, %f]\n", ((t_sq *)(obj->obj))->mat_ptr->attenuation.x,
				((t_sq *)(obj->obj))->mat_ptr->attenuation.y, ((t_sq *)(obj->obj))->mat_ptr->attenuation.z);
		}
		obj = obj->next;
	}
	printf("debug ok\n");
	return (1);
}
