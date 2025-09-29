#include "so_long.h"

int	copy_map(t_data *all, char ***copy)
{
	char	**new_grid;
	int		i;

	i = 0;
	*copy = NULL;
	new_grid = malloc(sizeof(char *) * (all->game.height + 1));
	if (!new_grid)
		return (-1);
	while (i < all->game.height)
	{
		new_grid[i] = ft_strdup(all->map[i]);
		if (!new_grid[i])
		{
			while (--i >= 0)
				free(new_grid[i]);
			free(new_grid);
			return (-1);
		}
		i++;
	}
	new_grid[i] = NULL;
	*copy = new_grid;
	return (0);
}

void	fill_map(char **map, int x, int y, t_game size)
{
	if (x < 0 || y < 0 || x >= size.width || y >= size.height
		|| map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	fill_map(map, x + 1, y, size);
	fill_map(map, x - 1, y, size);
	fill_map(map, x, y + 1, size);
	fill_map(map, x, y - 1, size);
}

int	flood_fill(t_data *all, char **copy)
{
	int	collectibles;
	int	exit_count;
	int	y;
	int	x;

	collectibles = 0;
	exit_count = 0;
	y = 0;
	fill_map(copy, all->game.player_pos.x, all->game.player_pos.y,
		all->game);
	while (y < all->game.height)
	{
		x = 0;
		while (x < all->game.width)
		{
			if (copy[y][x] == 'C')
				collectibles++;
			else if (copy[y][x] == 'E')
				exit_count++;
			x++;
		}
		y++;
	}
	return (collectibles == 0 && exit_count == 0);
}

int	is_all_reachable(t_data *data, char **copy)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->game.height)
	{
		x = 0;
		while (x < data->game.width)
		{
			if (copy[y][x] == 'C' || copy[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	copy_grid(t_data *all)
{
	int		success;
	char	**copy;

	success = 0;
	copy = NULL;
	if (copy_map(all, &copy) < 0)
	{
		cleanup_game(all);
		ft_printf("Error of allocate the memory");
		exit(-1);
	}
	success = flood_fill(all, copy);
	if (!success || !is_all_reachable(all, copy))
	{
		ft_printf("Map is not valid");
		free_map(copy);
		exit (-1);
	}
	free_map(copy);
}
