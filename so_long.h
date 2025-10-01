/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:07:43 by esergeev          #+#    #+#             */
/*   Updated: 2025/09/23 20:07:45 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "../libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_texture
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*book;
	void	*exit_i;
}			t_texture;

typedef struct s_pos
{
	int	x;
	int	y;
}			t_pos;

typedef struct s_game
{
	t_pos	player_pos;
	int		collect;
	int		collect_total;
	int		exit_flag;
	int		mouves;
	int		width;
	int		height;
	int		dy;
	int		dx;
	char	last_tile;
	int		key_w;
	int		key_a;
	int		key_s;
}			t_game;

typedef struct s_data
{
	t_game		game;
	char		**map;
	void		*win_ptr;
	void		*mlx_ptr;
	t_texture	texture;
}			t_data;

void	mouve_player(t_data *all, int dy, int dx);
int		key_hook(int keycode, void *param);
void	collectible(t_game *game, char **map);
void	position(t_data *all);
void	gaming(t_data *all);
void	remplisage(char **map, t_list *cur);
char	**parse_map(char *s, t_data *all);
int		is_rectangular(char **map);
int		is_enclosed_by_walls(char **map);
int		check_args(int ac, char **av);

void	load_textures(void *mlx_ptr, t_texture *texture);
int		window_close(t_data *all);
void	render_map(char **map, t_data *all);
void	init_window_sizes(char **map, int *width, int *height);
int		close_win(void *param);
void	*work_window(int width, int height, t_data *all);
void	cleanup_game(t_data *all);
int		copy_map(t_data *all, char ***copy);
void	free_map(char **map);
void	copy_grid(t_data *all);
int		valid_type_extension(char *s);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		game_loop(void *param);

#endif
