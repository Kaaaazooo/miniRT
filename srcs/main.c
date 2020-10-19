/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:29:31 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/19 14:21:20 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		main(int ac, char **av)
{
	t_conf	*conf;
	t_mlx	mlx;

	check_arg(ac, av);
	if (!(mlx.ptr = mlx_init()))
		ft_handle_error("Minilibx failed to initialize\n", NULL);
	conf = read_file(av[1], &mlx);
	conf->seed.a += conf->seed.a ? 0 : (unsigned int)conf;
	if (!(mlx.win = mlx_new_window(mlx.ptr, conf->res->x,
								conf->res->y, "my_miniRT")))
		ft_handle_error("Minilibx failed to create a new window\n", conf);
	conf->cam = conf->cams;
	render(conf);
	if (ac == 3)
		save_img(conf);
	else
	{
		mlx_put_image_to_window(conf->mlx->ptr, conf->mlx->win,
			conf->cam->img_ptr, 0, 0);
		handle_events(conf);
	}
	return (0);
}
/*
**	print_objs(conf);
**	printf("Rendering finished\n");
*/
