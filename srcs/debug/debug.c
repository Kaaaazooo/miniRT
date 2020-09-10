/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:03:34 by sabrugie          #+#    #+#             */
/*   Updated: 2020/03/08 12:11:07 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		print_objs(t_conf *config)
{
	t_cam		*cam;
	t_light		*light;
	t_obj		*obj;
	t_sphere	*sphere;

	cam = config->cam;
	light = config->lights;
	obj = config->objs;

	printf("\nRESOLUTION :\n");
	printf("[%d, %d]\n", config->res->x, config->res->y);
	printf("\nAMBIENT LIGHT :\n");
	printf("[%f] ; [%f, %f, %f]\n", config->amb_l->amb_rat,
			config->amb_l->amb_rgb.x, config->amb_l->amb_rgb.y,
			config->amb_l->amb_rgb.z);
	printf("\nCAMERAS :\n");
	while (cam)
	{
		printf("%p :\n", cam);
		printf("[%f, %f, %f] ; [%f, %f, %f] ; [%f, %f, %f] ; [%f]\n",
			cam->coord.x, cam->coord.y, cam->coord.z,
			cam->vec.x, cam->vec.y, cam->vec.z,
			cam->vup.x, cam->vup.y, cam->vup.z,
			cam->fov);
		cam = cam->next;
	}
	printf("\nLIGHTS :\n");
	while (light)
	{
		printf("[%f, %f] ; [%f] ; [%f, %f, %f]\n", light->coord.x, light->coord.y,
			light->ratio,
			light->rgb.x, light->rgb.y, light->rgb.z);
		light = light->next;
	}
	printf("OBJECTS :\n");
	while (obj)
	{
		sphere = obj->obj;
		printf("[%f, %f, %f] ; [%f] ; ", sphere->center.x,
		sphere->center.y, sphere->center.z, sphere->radius);
		printf("[%f, %f, %f]\n", sphere->mat_ptr->attenuation.x,
			sphere->mat_ptr->attenuation.y, sphere->mat_ptr->attenuation.z);
		obj = obj->next;
	}
	printf("STOP\n");
	return (1);
}
