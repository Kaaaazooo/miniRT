/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:48:46 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 19:11:02 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_cam	*cam_get_image(t_cam *cam, t_conf *conf, t_mlx *mlx, t_coord *res)
{
	if (!(cam->img_ptr = mlx_new_image(mlx->ptr, res->x, res->y)))
		ft_handle_error("mlx_new_image failed\n", conf);
	if (!(cam->data = mlx_get_data_addr(cam->img_ptr, &cam->bpp,
				&cam->line, &cam->endian)))
		ft_handle_error("mlx_get_data_addr failed\n", conf);
	return (cam);
}

t_cam	*init_cam(t_conf *conf, t_mlx *mlx, t_coord *res, float aspect)
{
	float	theta;
	float	half_height;
	float	half_width;
	t_vec	u;
	t_vec	v;

	if (!conf->cam)
		return (0);
	theta = conf->cam->fov * (M_PI / 180);
	theta = 2 * atan(tan(theta / 2) * aspect);
	v_unit(&conf->cam->vec, &conf->cam->vec);
	half_height = tan(theta / 2);
	half_width = aspect * half_height;
	v_unit(&u, v_cross(&u, &conf->cam->vup, &conf->cam->vec));
	v_cross(&v, &conf->cam->vec, &u);
	v_mul(&conf->cam->ho, &u, half_width);
	v_mul(&conf->cam->ve, &v, half_height);
	v_sub(&conf->cam->llc, &conf->cam->pos, &conf->cam->vec);
	v_sub(&conf->cam->llc, &conf->cam->llc, &conf->cam->ho);
	v_sub(&conf->cam->llc, &conf->cam->llc, &conf->cam->ve);
	v_mul(&conf->cam->ho, &u, 2 * half_width);
	v_mul(&conf->cam->ve, &v, 2 * half_height);
	cam_get_image(conf->cam, conf, mlx, res);
	return ((conf->cam && (conf->cam = conf->cam->next) &&
	init_cam(conf, mlx, res, aspect) != NULL) ? conf->cam : 0);
}
