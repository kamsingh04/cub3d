/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamsingh <kamsingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 03:15:05 by kamsingh          #+#    #+#             */
/*   Updated: 2024/08/01 11:55:21 by kamsingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	pos_check(t_game *game, double y, double x)
{
	int	map_x;
	int	map_y;

	map_x = (int)x / TILE;
	map_y = (int)y / TILE;
	if (map_x <= 0 || map_x >= game->info->map_width ||
		map_y <= 0 || map_y >= game->info->map_length)
		return (0);
	if (game->info->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	rotate_cal(t_game *game, int direction)
{
	game->hero->angle += direction * ROT;
	if (game->hero->angle < 0)
		game->hero->angle += 2 * M_PI;
	else if (game->hero->angle > 2 * M_PI)
		game->hero->angle -= 2 * M_PI;
}

void	move_cal(t_game *data, double *movex, double *movey)
{
	double	angle;

	angle = data->hero->angle;
	*movex = 0;
	*movey = 0;
	if (data->hero->lefty_righty)
	{
		*movex -= data->hero->lefty_righty * sin(angle) * SPEED;
		*movey += data->hero->lefty_righty * cos(angle) * SPEED;
	}
	if (data->hero->down_up)
	{
		*movex += data->hero->down_up * cos(angle) * SPEED;
		*movey += data->hero->down_up * sin(angle) * SPEED;
	}
}

void	handle_player(t_game *data)
{
	double	movex;
	game	movey;
	int		newx;
	int		newy;

	if (data->hero->rotated)
		rotate_cal(data, data->hero->rotated);
	move_cal(data, &movex, &movey);
	newx = roundf(data->hero->x + movex);
	newy = roundf(data->hero->y + movey);
	if (pos_check(data, newy, newx))
	{
		data->hero->x = newx;
		data->hero->y = newy;
	}
}