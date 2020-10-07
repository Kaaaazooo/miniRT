/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:48:46 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/05 15:20:20 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_cam	*cam_get_image(t_cam *cam, t_mlx *mlx, int x, int y)
{
	if (!(cam->img_ptr = mlx_new_image(mlx->ptr, x, y)))
		ft_handle_error("mlx_new_image failed\n");
	if (!(cam->data = mlx_get_data_addr(cam->img_ptr, &cam->bpp,
				&cam->line, &cam->endian)))
		ft_handle_error("mlx_get_data_addr failed\n");
	return (cam);
}

t_cam	*init_cam(t_cam *cam, t_mlx *mlx, t_coord *res, float aspect)
{
	float	theta;
	float	half_height;
	float	half_width;
	t_vec	u;
	t_vec	v;

	if (!cam)
		return (0);
	theta = cam->fov * (M_PI / 180);
	theta = 2 * atan(tan(theta / 2) * aspect);
	v_unit(&cam->vec, &cam->vec);
	half_height = tan(theta / 2);
	half_width = aspect * half_height;
	v_unit(&u, v_cross(&u, &cam->vup, &cam->vec));
	v_cross(&v, &cam->vec, &u);
	v_mul(&cam->ho, &u, half_width);
	v_mul(&cam->ve, &v, half_height);
	v_sub(&cam->llc, &cam->pos, &cam->vec);
	v_sub(&cam->llc, &cam->llc, &cam->ho);
	v_sub(&cam->llc, &cam->llc, &cam->ve);
	v_mul(&cam->ho, &u, 2 * half_width);
	v_mul(&cam->ve, &v, 2 * half_height);
	cam_get_image(cam, mlx, res->x, res->y);
	return ((cam && init_cam(cam->next, mlx, res, aspect) != NULL)
			? cam : 0);
}
