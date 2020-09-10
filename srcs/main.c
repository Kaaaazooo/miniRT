/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:29:31 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:30:03 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	*color(t_vec *dest, t_ray r, t_conf *conf, int depth)
{
	t_vec		tmp;
	t_vec		tmp2;
	t_hit		hit;
	t_hit_rec	rec;
	float		t;

	hit.r = r;
	hit.t_min = 0.001;
	hit.t_max = FLT_MAX;
	if (hit_any(conf->objs, &hit, &rec))
	{
		if (depth < 19 && scatter(&rec, &conf->seed, &r))
			return (v_prod(dest, &conf->amb_l->amb_rgb, v_prod(dest,
								&rec.mat_ptr->attenuation, color(dest,
								rec.mat_ptr->scattered, conf, depth + 1))));
		else
			return (new_vec(dest, 0, 0, 0));
	}
	v_unit(&tmp, &r.dir);
	t = 0.5 * (tmp.y + 1);
	v_mul(&tmp, new_vec(&tmp2, 1, 1, 1), (1 - t) * conf->amb_l->amb_rat);
	v_prod(&tmp2, new_vec(&tmp2, 0.5, 0.7, 1.0), &conf->amb_l->amb_rgb);
	v_mul(&tmp2, &tmp2, t);
	return (v_add(dest, &tmp, &tmp2));
}

t_vec	*ft_anti_aliasing(t_vec *col, t_ray *r, t_coord *coord, t_conf *conf)
{
	t_vec	save;
	int		s;
	float	u;
	float	v;

	s = 0;
	u = 0;
	v = 0;
	new_vec(col, 0, 0, 0);
	while (s < 49)
	{
		u = (float)(coord->x + my_rand(&conf->seed)) / (float)conf->res->x;
		v = (float)(coord->y + my_rand(&conf->seed)) / (float)conf->res->y;
		get_ray(r, conf->cam, u, v);
		v_add(col, col, color(&save, *r, conf, 0));
		s++;
	}
	v_div(col, col, 49);
	col->x = sqrt(col->x);
	col->y = sqrt(col->y);
	col->z = sqrt(col->z);
	return (col);
}

int		main(int ac, char **av)
{
	t_conf	*conf;
	t_coord	coord;
	t_mlx	mlx;
	t_ray	r;
	t_vec	col;

	check_arg(ac, av[1], &mlx);
	coord.x = 0;
	conf = read_file(av[1]);
	conf->seed.a += conf->seed.a ? 0 : (unsigned int)conf;
	print_objs(conf);
	mlx.win = mlx_new_window(mlx.ptr, conf->res->x, conf->res->y, "miniRT");
	while (coord.x < conf->res->x)
	{
		coord.y = conf->res->y;
		while (coord.y)
		{
			ft_anti_aliasing(&col, &r, &coord, conf);
			mlx_pixel_put(mlx.ptr, mlx.win,
			coord.x, conf->res->y - coord.y--, v_rgb(&col));
		}
		++coord.x;
	}
	printf("ok\n");
	mlx_loop(mlx.ptr);
	return (0);
}
