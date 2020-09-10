/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:48:46 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:30:47 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_cam	*init_cam(t_cam *cam, float aspect)
{
	float	theta;
	float	half_height;
	float	half_width;
	t_vec	u;
	t_vec	v;

	if (!cam)
		return (0);
	v_unit(&cam->vec, &cam->vec);
	theta = cam->fov * M_PI / 180;
	half_height = tan(theta / 2);
	half_width = aspect * half_height;
	v_unit(&u, v_cross(&u, &cam->vup, &cam->vec));
	v_cross(&v, &cam->vec, &u);
	v_mul(&cam->ho, &u, half_width);
	v_mul(&cam->ve, &v, half_height);
	v_sub(&cam->llc, &cam->coord, &cam->vec);
	v_sub(&cam->llc, &cam->llc, &cam->ho);
	v_sub(&cam->llc, &cam->llc, &cam->ve);
	v_mul(&cam->ho, &u, 2 * half_width);
	v_mul(&cam->ve, &v, 2 * half_height);
	if (cam && init_cam(cam->next, aspect) != NULL)
		return (cam);
	return (0);
}
