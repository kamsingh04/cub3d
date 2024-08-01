/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamsingh <kamsingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:14:02 by ashirzad          #+#    #+#             */
/*   Updated: 2024/07/31 15:12:10 by kamsingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_info(t_info *info_t)
{
	printf("north = %s\n", info_t->north);
	printf("south = %s\n", info_t->south);
	printf("west = %s\n", info_t->west);
	printf("east = %s\n", info_t->east);
	printf("floor = %s\n", info_t->floor);
	printf("ceiling = %s\n", info_t->ceiling);
	printf("map\n\n");
	int i = 0;
	while (info_t->map[i])
	{
		printf("%s\n", info_t->map[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
    int fd;
    int i;
    char *tab[100];
    char *line;
    t_info *info_t;
    t_game game; // Declare the t_game struct here

    i = 0;
    if (argc != 2)
    {
        printf("error : two args required\n");
        return (-1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf("error : file name\n");
        return (-1);
    }
    while ((line = get_next_line(fd)))
    {
        tab[i++] = ft_strdup(line);
        free(line);
    }
    tab[i] = NULL;
    close(fd);
    if (check_file(tab) == -1)
        return (-1);
    info_t = ft_parse(tab);
    if (info_t == NULL)
        return (-1);
    print_info(info_t);
	start_the_game(&game);
    return (0);
}
