/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:17:59 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 19:48:59 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_conf	*init_conf(t_mlx *mlx)
{
	t_conf	*conf;

	if (!(conf = malloc(sizeof(t_conf))))
		ft_handle_error("Init conf : malloc failed\n", NULL);
	conf->res = 0;
	conf->amb_l = 0;
	conf->cam = 0;
	conf->lights = 0;
	conf->objs = 0;
	conf->mlx = mlx;
	return (conf);
}

int		parse(t_conf *conf, char *str)
{
	if (str[0] == 'R')
		return (parse_r(&conf->res, conf, str + 1));
	else if (str[0] == 'A')
		return (parse_a(&conf->amb_l, conf, str + 1));
	else if (str[0] == 'c' && str[1] == 'y')
		return (parse_cy(&conf->objs, conf, str + 2));
	else if (str[0] == 'c')
		return (parse_c(&conf->cam, conf, str + 1));
	else if (str[0] == 'l')
		return (parse_l(&conf->lights, conf, str + 1));
	else if (str[0] == 's' && str[1] == 'p')
		return (parse_sp(&conf->objs, conf, str + 2));
	else if (str[0] == 'p' && str[1] == 'l')
		return (parse_pl(&conf->objs, conf, str + 2));
	else if (str[0] == 's' && str[1] == 'q')
		return (parse_sq(&conf->objs, conf, str + 2));
	else if (str[0] == 't' && str[1] == 'r')
		return (parse_tr(&conf->objs, conf, str + 2));
	return (ft_handle_error("Invalid type\n", conf));
}

t_conf	*read_file(char *filename, t_mlx *mlx)
{
	int		fd;
	int		ret;
	char	*line;
	t_conf	*conf;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_handle_error("Cannot open file\n", NULL);
	conf = init_conf(mlx);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (*line)
			parse(conf, line);
		free(line);
	}
	if (*line && fd >= 0)
		parse(conf, line);
	free(line);
	if (!conf->res || !conf->amb_l)
		ft_handle_error(conf->res ?
			"No ambient light\n" : "No resolution\n", conf);
	if (!(conf->cams = conf->cam))
		ft_handle_error("No camera\n", conf);
	init_cam(conf, mlx, conf->res,
		(float)conf->res->x / (float)conf->res->y);
	return (conf);
}
