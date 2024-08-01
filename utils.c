/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:57:44 by ashirzad          #+#    #+#             */
/*   Updated: 2024/07/30 15:41:13 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	what_isit(char *str)
{
	char	**argv;
	int		exit;

	exit = 0;
	argv = ft_split(str, ' ');
	if (argv == NULL)
		return (-1);
	if (ft_strcmp(argv[0], "NO") == 0)
		exit = 1;
	else if (!ft_strcmp(argv[0], "SO"))
		exit = 2;
	else if (!ft_strcmp(argv[0], "WE"))
		exit = 3;
	else if (!ft_strcmp(argv[0], "EA"))
		exit = 4;
	else if (!ft_strcmp(argv[0], "F"))
		exit = 5;
	else if (!ft_strcmp(argv[0], "C"))
		exit = 6;
	else if (argv[0][0] == '1' || argv[0][0] == '0' || argv[0][0] == '2')
		exit = 7;
	else if (argv[0][0] == '\n')
		exit = 8;
	free_list(argv);
	return (exit);
}

int	list_len(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}


void	free_list(char **list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return ;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

int	ft_rgba(char **argv)
{
	if (argv == NULL)
		return (-1);
	if (list_len(argv) != 3 || argv[2][0] == '\n')
	{
		printf("error : invalid rgb\n");
		free_list(argv);
		return (-1);
	}
	else if (ft_atoi(argv[0]) < 0 || ft_atoi(argv[0]) > 255 || \
		ft_atoi(argv[1]) < 0 || ft_atoi(argv[1]) > 255 || \
		ft_atoi(argv[2]) < 0 || ft_atoi(argv[2]) > 255)
	{
		printf("error : rgba range 0 - 255\n");
		free_list(argv);
		return (-1);
	}
	return (0);
}
