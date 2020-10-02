/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:29:31 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/02 12:51:24 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	hit_light(t_conf *conf, t_light *light, t_vec *light_v, t_hit_rec *rec)
{
	t_hit		hit;
	t_hit_rec	l_rec;

	if (rec->mat_ptr->type != PL && rec->mat_ptr->type != SQ &&
		rec->mat_ptr->type != TR)
		return (1);
	hit.t_min = 0.01;
	hit.t_max = FLT_MAX;
	hit.ray.pos = light->pos;
	hit.ray.dir = *light_v;
	if (hit_any(conf->objs, &hit, &l_rec) && l_rec.t != FLT_MAX)
		if (rec->mat_ptr != l_rec.mat_ptr)
			return (1);
	return (-1);
}

t_vec	*get_light_at(t_vec *color, t_conf *conf, t_light *light,
														t_hit_rec *rec)
{
	float		dot;
	t_vec		tmp_v;
	t_hit		hit;
	t_hit_rec	l_rec;

	hit.t_min = 0.01;
	hit.ray.pos = rec->p;
	while (light)
	{
		hit.t_max = v_len(v_sub(&tmp_v, &light->pos, &rec->p));
		v_unit(&hit.ray.dir, v_sub(&hit.ray.dir, &light->pos, &rec->p));
		dot = v_dot(&rec->normal, &hit.ray.dir);
		if (!hit_any(conf->objs, &hit, &l_rec) || l_rec.mat_ptr == rec->mat_ptr)
			if (dot > 0)
			{
				v_mul(&tmp_v, &light->rgb, light->ratio * dot);
				v_add(color, color, v_prod(&tmp_v, &tmp_v,
										&rec->mat_ptr->attenuation));
			}
		light = light->next;
	}
	color->x = color->x > 1 ? 1 : color->x;
	color->y = color->y > 1 ? 1 : color->y;
	color->z = color->z > 1 ? 1 : color->z;
	return (color);
}

t_vec	*pixel_color(t_vec *color, t_ray ray, t_conf *conf)
{
	t_hit		hit;
	t_hit_rec	rec;
	t_light		*light;

	hit.t_min = 0.001;
	hit.t_max = FLT_MAX;
	hit.ray = ray;
	new_vec(color, 0, 0, 0);
	if (hit_any(conf->objs, &hit, &rec))
	{
		v_prod(color, &rec.mat_ptr->attenuation,
					v_mul(color, &conf->amb_l->rgb, conf->amb_l->ratio));
		light = conf->lights;
		get_light_at(color, conf, light, &rec);
	}
	return (color);
}

void	render(t_conf *conf, t_mlx *mlx, t_coord coord)
{
	t_ray	ray;
	t_vec	color;
	int		i;

	while (coord.x < conf->res->x)
	{
		coord.y = 0;
		while (coord.y < conf->res->y)
		{
			get_ray(&ray, conf->cam, (float)(coord.x) / (float)(conf->res->x),
									(float)(coord.y) / (float)(conf->res->y));
			pixel_color(&color, ray, conf);
			i = coord.x * (conf->cam->bpp / 8) + 
				(conf->res->y - coord.y) * conf->cam->line;
			v_mul(&color, &color, 255);
			conf->cam->data[i] = color.x;
			conf->cam->data[i + 1] = color.y;
			conf->cam->data[i + 2] = color.z;
			++coord.y;
			//mlx_pixel_put(mlx->ptr, mlx->win,
			//coord.x, conf->res->y - coord.y++, v_rgb(&color));
		}
		++coord.x;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win,
		conf->cam->img_ptr, 0, 0);
}

int		main(int ac, char **av)
{
	t_conf	*conf;
	t_coord	coord;
	t_mlx	mlx;

	check_arg(ac, av[1]);
	if (!(mlx.ptr = mlx_init()))
		ft_handle_error("Minilibx failed to initialize\n");
	coord.x = 0;
	conf = read_file(av[1], &mlx);
	conf->seed.a += conf->seed.a ? 0 : (unsigned int)conf;
	print_objs(conf);
	if (!(mlx.win = mlx_new_window(mlx.ptr, conf->res->x,
								conf->res->y, "my_miniRT")))
		ft_handle_error("Minilibx failed to create a new window\n");
	conf->cams = conf->cam;
	render(conf, &mlx, coord);
	printf("Rendering finished\n");
	mlx_loop(mlx.ptr);
	exit(0);
	return (0);
}
