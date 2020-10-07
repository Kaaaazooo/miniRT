/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 11:18:22 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/07 15:24:56 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		switch_cam(int key, t_conf *conf)
{
	t_cam	*cam;

	cam = conf->cams;
	if (key == 123)
	{
		if (conf->cam == conf->cams)
			while (conf->cam->next)
				conf->cam = conf->cam->next;
		else
		{
			while (cam->next != conf->cam)
				cam = cam->next;
			conf->cam = cam;
		}
	}
	if (key == 124)
	{
		if (!conf->cam->next)
			conf->cam = conf->cams;
		else
			conf->cam = conf->cam->next;
	}
	render(conf);
	return (mlx_put_image_to_window(conf->mlx->ptr,
				conf->mlx->win, conf->cam->img_ptr, 0, 0));
}

int		key_events(int key, void *ptr)
{
	if (key == 53)
		ft_handle_error("Closing miniRT...\n");
	if (key == 123 || key == 124)
		switch_cam(key, (t_conf*)ptr);
	return (0);
}

void	handle_events(t_conf *conf)
{
	mlx_hook(conf->mlx->win, 17, 0, ft_handle_error,
						(void *)"Closing miniRT...\n");
	mlx_key_hook(conf->mlx->win, key_events, (void *)conf);
	mlx_loop(conf->mlx->ptr);
}
