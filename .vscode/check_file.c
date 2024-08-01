/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:34:37 by ashirzad          #+#    #+#             */
/*   Updated: 2024/07/30 15:53:59 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_values(char **tab)
{
	char	**argv;
	char	**rgba;
	int		exit;
	int		i;

	i = 0;
	exit = 0;
	argv = NULL;
	while (tab[i])
	{
		argv = ft_split(tab[i], ' ');
		if (what_isit(tab[i]) < 7 && list_len(argv) != 2)
			exit = -1;
		else if (what_isit(tab[i]) == 5 || what_isit(tab[i]) == 6)
		{
			rgba = ft_split(argv[1], ',');
			if (ft_rgba(rgba) == -1)
				exit = -1;
		}
		free_list(argv);
		i++;
	}
	return (exit);
}

int	check_vars(t_parse *parse)
{
	if (parse->north == 0)
		return (printf("error : no var north\n"));
	else if (parse->north > 1)
		return (printf("error : north dup\n"));
	if (parse->south == 0)
		return (printf("error : no var south\n"));
	else if (parse->south > 1)
		return (printf("error : north south\n"));
	if (parse->west == 0)
		return (printf("error : no var west\n"));
	else if (parse->west > 1)
		return (printf("error : west dup\n"));
	if (parse->east == 0)
		return (printf("error : no var east\n"));
	else if (parse->east > 1)
		return (printf("error : east dup\n"));
	if (parse->floor == 0)
		return (printf("error : no var floor\n"));
	else if (parse->floor > 1)
		return (printf("error : floor dup\n"));
	if (parse->ceiling == 0)
		return (printf("error : no var ceiling\n"));
	else if (parse->ceiling > 1)
		return (printf("error : ceiling dup\n"));
	return (0);
}

int	init_vars(char **tab, t_parse *parse)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (what_isit(tab[i]) == 1)
			parse->north += 1;
		else if (what_isit(tab[i]) == 2)
			parse->south += 1;
		else if (what_isit(tab[i]) == 3)
			parse->west += 1;
		else if (what_isit(tab[i]) == 4)
			parse->east += 1;
		else if (what_isit(tab[i]) == 5)
			parse->floor += 1;
		else if (what_isit(tab[i]) == 6)
			parse->ceiling += 1;
		else if (what_isit(tab[i]) == 0)
		{
			printf("error : unknwon var %s", tab[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	init_parse(t_parse *parse)
{
	parse->north = 0;
	parse->south = 0;
	parse->west = 0;
	parse->east = 0;
	parse->floor = 0;
	parse->ceiling = 0;
}

int	check_file(char **tab)
{
	t_parse	*parse;
	char	**map;
	int		exit;

	map = NULL;
	parse = malloc(sizeof(t_parse));
	if (parse == NULL)
		return (-1);
	init_parse(parse);
	if (init_vars(tab, parse) == -1 || check_vars(parse) != 0)
		exit = -1;
	if (check_values(tab))
	{
		printf("error : invalid values\n");
		exit = -1;
	}
	map = ft_map(tab);
	if (check_map(map) == -1)
		return (-1);
	return (exit);
}
