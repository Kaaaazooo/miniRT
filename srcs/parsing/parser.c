/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:17:59 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/21 13:57:09 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_conf	*init_conf(void)
{
	t_conf	*config;

	if (!(config = malloc(sizeof(t_conf))))
		ft_handle_error("malloc failed\n");
	config->res = 0;
	config->amb_l = 0;
	config->cam = 0;
	config->lights = 0;
	config->objs = 0;
	return (config);
}

int		parse(t_conf *config, char *str)
{
	if (str[0] == 'R')
		return (parse_r(&config->res, str + 1));
	else if (str[0] == 'A')
		return (parse_a(&config->amb_l, str + 1));
	else if (str[0] == 'c')
		return (parse_c(&config->cam, str + 1));
	else if (str[0] == 'l')
		return (parse_l(&config->lights, str + 1));
	else if (str[0] == 's' && str[1] == 'p')
		return (parse_sp(&config->objs, str + 2));
	else if (str[0] == 'p' && str[1] == 'l')
		return (parse_pl(&config->objs, str + 2));
	else if (str[0] == 's' && str[1] == 'q')
		return (parse_sq(&config->objs, str + 2));
	else if (str[0] == 'c' && str[1] == 'y')
		return (parse_cy(&config->objs, str + 2));
	else if (str[0] == 't' && str[1] == 'r')
		return (parse_tr(&config->objs, str + 2));
	return (ft_handle_error("Wrong input\n"));
}

t_conf	*read_file(char *filename)
{
	int		fd;
	int		ret;
	char	*line;
	t_conf	*config;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_handle_error("Cannot open file\n");
	config = init_conf();
	line = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (*line)
			parse(config, line);
		free(line);
	}
	if (*line && fd >= 0)
		parse(config, line);
	free(line);
	if (!config->res)
		ft_handle_error("No resolution\n");
	init_cam(config->cam, (float)config->res->x / (float)config->res->y);
	if (!config->cam)
		ft_handle_error("No camera\n");
	return (config);
}
