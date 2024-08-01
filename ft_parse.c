/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:57:03 by ashirzad          #+#    #+#             */
/*   Updated: 2024/07/30 16:21:41 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char *ft_value(char *str)
{
	char	**argv;
	char	*ptr;

	argv = ft_split(str, ' ');
	if (argv == NULL)
		return (NULL);
	ptr = malloc(sizeof(char *) * ft_strlen(argv[1]));
	ft_strncpy(ptr, argv[1], ft_strlen(argv[1]) - 1);
	free_list(argv);
	return (ptr);
}

t_info	*ft_parse(char **tab)
{
	t_info	*info_t;
	int		i;
	int		j;

	i = 0;
	j = 0;
	info_t = malloc(sizeof(t_info));
	if (info_t == NULL)
		return (NULL);
	while (tab[i])
	{
		if (what_isit(tab[i]) == 1)
			info_t->north = ft_value(tab[i]);
		else if (what_isit(tab[i]) == 2)
			info_t->south = ft_value(tab[i]);
		else if (what_isit(tab[i]) == 3)
			info_t->west = ft_value(tab[i]);
		else if (what_isit(tab[i] )== 4)
			info_t->east = ft_value(tab[i]);
		else if (what_isit(tab[i]) == 5)
			info_t->floor = ft_value(tab[i]);
		else if (what_isit(tab[i]) == 6)
			info_t->ceiling = ft_value(tab[i]);
		i++;
	}
	info_t->map = (char **)malloc(sizeof(char *) * (map_length(tab) + 1));
	if (info_t->map == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if (what_isit(tab[i]) == 7)
		{
			info_t->map[j] = malloc(sizeof(char *) * ft_strlen(tab[i]));
			ft_strncpy(info_t->map[j], tab[i], ft_strlen(tab[i]) - 1);
			j++;
		}
		i++;
	}
	info_t->map[j] = NULL;
	return (info_t);
}
