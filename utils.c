/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:07:55 by esergeev          #+#    #+#             */
/*   Updated: 2025/09/23 20:07:57 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	remplisage(char **map, t_list *cur)
{
	int	i;

	i = 0;
	while (cur)
	{
		map[i] = ft_strdup((char *)cur->content);
		cur = cur->next;
		i++;
	}
	map[i] = NULL;
}

int	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf("Usage: %s map.ber\n", av[0]);
		return (0);
	}
	if (!valid_type_extension(av[1]))
	{
		ft_printf("Valid extension only .ber\n");
		return (0);
	}
	return (1);
}

void	load_textures(void *mlx_ptr, t_texture *texture)
{
	int	width;
	int	height;

	texture->wall = mlx_xpm_file_to_image(mlx_ptr, "texture/wall.xpm",
			&width, &height);
	texture->floor = mlx_xpm_file_to_image(mlx_ptr, "texture/floor.xpm",
			&width, &height);
	texture->player = mlx_xpm_file_to_image(mlx_ptr, "texture/player.xpm",
			&width, &height);
	texture->book = mlx_xpm_file_to_image(mlx_ptr, "texture/book.xpm",
			&width, &height);
	texture->exit_i = mlx_xpm_file_to_image(mlx_ptr, "texture/exit_i.xpm",
			&width, &height);
	if (!texture->wall || !texture->floor || !texture->player
		|| !texture->book || !texture->exit_i)
	{
		write(2, "Error loading textures\n", 23);
		exit(1);
	}
}

void	render_tile(char tile, int x, int y, t_data *all)
{
	int	tile_size;

	tile_size = 32;
	if (tile == '1')
		mlx_put_image_to_window(all->mlx_ptr, all->win_ptr,
			all->texture.wall, x * tile_size, y * tile_size);
	else
		mlx_put_image_to_window(all->mlx_ptr, all->win_ptr,
			all->texture.floor, x * tile_size, y * tile_size);
	if (tile == 'P')
		mlx_put_image_to_window(all->mlx_ptr, all->win_ptr,
			all->texture.player, x * tile_size, y * tile_size);
	else if (tile == 'C')
		mlx_put_image_to_window(all->mlx_ptr, all->win_ptr,
			all->texture.book, x * tile_size, y * tile_size);
	else if (tile == 'E')
		mlx_put_image_to_window(all->mlx_ptr, all->win_ptr,
			all->texture.exit_i, x * tile_size, y * tile_size);
}

void	render_map(char **map, t_data *all)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			render_tile(map[y][x], x, y, all);
			x++;
		}
		y++;
	}
}
