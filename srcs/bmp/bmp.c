/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:45:50 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/07 15:26:22 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	get_bmp_data(t_conf *conf, unsigned char *header)
{
	unsigned char	bmp_pad[3];
	int				fd;
	int				i;
	int				padding;

	fd = open("save.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	write(fd, header, 54);
	i = conf->res->y;
	padding = (4 - (conf->res->x * 4) % 4) % 4;
	ft_bzero(bmp_pad, 3);
	while (--i >= 0)
	{
		write(fd, conf->cam->data + (i * conf->cam->line), conf->cam->line);
		write(fd, bmp_pad, padding);
	}
}

void	save_img(t_conf *conf)
{
	unsigned char	header[54];
	int				size;

	size = 54 + (3 * conf->res->x +
		((4 - (conf->res->x * 4) % 4) % 4)) * conf->res->y;
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	header[2] = size;
	header[3] = size >> 8;
	header[4] = size >> 16;
	header[5] = size >> 24;
	header[10] = 54;
	header[14] = 40;
	header[18] = conf->res->x;
	header[19] = conf->res->x >> 8;
	header[20] = conf->res->x >> 16;
	header[21] = conf->res->x >> 24;
	header[22] = conf->res->y;
	header[23] = conf->res->y >> 8;
	header[24] = conf->res->y >> 16;
	header[25] = conf->res->y >> 24;
	header[26] = 1;
	header[28] = conf->cam->bpp;
	get_bmp_data(conf, header);
}
