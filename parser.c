/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:07:23 by esergeev          #+#    #+#             */
/*   Updated: 2025/09/23 20:07:26 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_list	*get_lines(int fd)
{
	t_list	*lst;
	char	*line;
	int		len;

	lst = NULL;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		ft_lstadd_back(&lst, ft_lstnew(line));
		line = get_next_line(fd);
	}
	return (lst);
}

char	**parse_map(char *s, t_data *all)
{
	int		fd;
	t_list	*lst;
	int		i;

	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lst = get_lines(fd);
	close(fd);
	i = ft_lstsize(lst);
	all->map = malloc(sizeof(char *) * (i + 1));
	if (!all->map)
	{
		ft_lstclear(&lst, free);
		return (NULL);
	}
	remplisage(all->map, lst);
	ft_lstclear(&lst, free);
	return (all->map);
}

static int	check_row(char *row)
{
	int	j;

	j = 0;
	while (row[j])
	{
		if (row[j] != '1')
			return (0);
		j++;
	}
	return (1);
}

static int	check_side_walls(char **map, int height, int width)
{
	int	i;

	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_enclosed_by_walls(char **map)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (map[height])
		height++;
	while (map[0][width])
		width++;
	if (!check_row(map[0]) || !check_row(map[height - 1]))
		return (0);
	if (!check_side_walls(map, height, width))
		return (0);
	return (1);
}
