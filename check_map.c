#include "so_long.h"

int	valid_type_extension(char *s)
{
	int		len;
	char	*ext;

	len = ft_strlen(s);
	if (len < 5)
	{
		ft_printf("Invalid file name\n");
		return (0);
	}
	ext = s + len - 4;
	if (!ft_strncmp(ext, ".ber", 4))
		return (1);
	return (0);
}

