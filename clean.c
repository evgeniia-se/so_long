#include "so_long.h"


int	close_win(void *param)
{
	(void)param;
	exit(0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free (map[i]);
		i++;
	}
	free(map);
}

void	free_tex(void *mlx_ptr, t_texture *tex)
{
	if (tex->wall)
		mlx_destroy_image(mlx_ptr, tex->wall);
	if (tex->floor)
		mlx_destroy_image(mlx_ptr, tex->floor);
	if (tex->player)
		mlx_destroy_image(mlx_ptr, tex->player);
	if (tex->book)
		mlx_destroy_image(mlx_ptr, tex->book);
	if (tex->exit_i)
		mlx_destroy_image(mlx_ptr, tex->exit_i);
}

void	cleanup_game(t_data *all)
{
	free_map(all->map);
	free_tex(all->mlx_ptr, &(all->texture));
	if (all->win_ptr)
	{
		mlx_clear_window(all->mlx_ptr, all->win_ptr);
		mlx_destroy_window(all->mlx_ptr, all->win_ptr);
	}
}

int	window_close(t_data *all)
{
	ft_printf("Escape the game\n");
	cleanup_game(all);
	exit(0);
}
