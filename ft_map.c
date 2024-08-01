/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamsingh <kamsingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:36:50 by ashirzad          #+#    #+#             */
/*   Updated: 2024/08/01 11:45:33 by kamsingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	map_length(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i] && what_isit(tab[i]) != 7)
		i++;
	if (tab[i] == NULL)
	{
		printf("error : there is no map\n");
		return (0);
	}
	while (tab[i])
	{
		if (what_isit(tab[i]) != 7)
		{
			printf("error : invalid map\n");
			return (0);
		}
		j++;
		i++;
	}
	return (j);
}

int	only_character(char *str, int c)
{
	while (*(str + 1))
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}

int	closed_map(char **map)
{
	int	i;

	i = 0;
	if (!only_character(map[0], '1'))
		return (-1);
	while (map[i])
	{
		if (map[i][0] != '1' || map[i] \
			[ft_strlen(map[i]) - 2] != '1')
			return (-1);
		i++;
	}
	if (!only_character(map[i - 1], '1'))
		return (-1);
	return (0);
}

char	**ft_map(char **tab)
{
	int		i;
	int		j;
	char	**map;
	int		len;

	i = 0;
	j = 0;
	len = map_length(tab);
	if (!len)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (len + 1));
	if (map == NULL)
		return (NULL);
	while (tab[i] && what_isit(tab[i]) != 7)
		i++;
	while (tab[i])
		map[j++] = ft_strdup(tab[i++]);
	map[j] = NULL;
	return (map);
}

int	valid_character(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' \
				&& map[i][j] != 'S' && map[i][j] != 'N' \
				&& map[i][j] != '\n' && map[i][j] != 'W' \
				&& map[i][j] != 'E' && map[i][j] != '2')
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	dup_item(char **map)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || \
				map[i][j] == 'W' || map[i][j] == 'E')
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

int	check_map(char **map)
{
	int	exit;

	exit = 0;
	if (map == NULL)
		return (-1);
	if (closed_map(map) == -1)
	{
		printf("error : map is not closed\n");
		exit = -1;
	}
	if (valid_character(map) == -1)
	{
		printf("error : not defined character\n");
		exit = -1;
	}
	if (dup_item(map) != 1)
	{
		printf("error : choose one side for player\n");
		exit = -1;
	}
	free_list(map);
	return (exit);
}


