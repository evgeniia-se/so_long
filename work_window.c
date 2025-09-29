/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:08:08 by esergeev          #+#    #+#             */
/*   Updated: 2025/09/23 20:08:10 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(char **map)
{
	int	row_len;
	int	i;
	int	j;

	row_len = 0;
	i = 0;
	while (map[0][row_len])
		row_len++;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j != row_len)
			return (0);
		i++;
	}
	return (1);
}

int	key_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307)
		window_close(data);
	if (keycode == 119)
		mouve_player(data, -1, 0);
	if (keycode == 97)
		mouve_player(data, 0, -1);
	if (keycode == 115)
		mouve_player(data, 1, 0);
	if (keycode == 100)
		mouve_player(data, 0, 1);
	return (0);
}

void	init_window_sizes(char **map, int *width, int *height)
{
	*width = 0;
	*height = 0;
	while (map[0][*width])
		(*width)++;
	while (map[*height])
		(*height)++;
}

int	expose_hook(void *param)
{
	t_data	*all;

	all = (t_data *)param;
	render_map(all->map, all);
	return (0);
}

void	*work_window(int width, int height, t_data *all)
{
	all->mlx_ptr = mlx_init();
	if (!all->mlx_ptr)
		return (NULL);
	all->win_ptr = mlx_new_window(all->mlx_ptr, width * 32,
			height * 32, "so_long");
	if (!all->win_ptr)
		return (NULL);
	load_textures(all->mlx_ptr, &all->texture);
	render_map(all->map, all);
	mlx_hook(all->win_ptr, 17, 0L, close_win, NULL);
	mlx_key_hook(all->win_ptr, key_hook, all);
	mlx_expose_hook(all->win_ptr, expose_hook, all);
	return (all->mlx_ptr);
}
