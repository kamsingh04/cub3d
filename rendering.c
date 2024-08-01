/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamsingh <kamsingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 03:20:29 by kamsingh          #+#    #+#             */
/*   Updated: 2024/08/01 12:05:47 by kamsingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_outside_screen(int x, int y, int screen_width, int screen_height)
{
	if (x < 0 || x >= screen_width || y < 0 || y >= screen_height)
		return (1);
	return (0);
}

void	set_pixel(t_game *data, int x, int y, int color)
{
	if (is_outside_screen(x, y, data->screen_width, data->screen_height))
		return ;
	mlx_put_pixel(data->img, x, y, color);
}

void	render_background(t_game *data, int ray,
		int top_pixel, int bottom_pixel)
{
	int	i;
	int	j;

	j = top_pixel;
	i = bottom_pixel;
	while (i < data->screen_height)
		set_pixel(data, ray, i, data->cub->floor_color);
	i++:
		while (j < top_pixel)
		set_pixel(data, ray, i, data->cub->ceiling_color);
	j++:
}

void	determine_texture(t_game *data)
{
		data->ray->rayangle = normalize_angle(data->ray->rayangle);
	while (1)
	{
	if (data->ray->wallflag == 0)
	{
		if (data->ray->rayangle > M_PI / 2 &&
			data->ray->rayangle < 3 * M_PI / 2)
		{
			data->texture = data->textures.west;
			break;
		}
		else
		{
			data->texture = data->textures.east;
			break;
		}
	}
	else
	{
		if (data->ray->rayangle > 0 && data->ray->rayangle < M_PI)
		{
			data->texture = data->textures.south;
			break;
		}
		else
		{
			data->texture = data->textures.north;
			break;
		}
	}
}
}

void	render_ray(t_game *data, int ray)
{
	double	wall_height;
	double	bottom_pixel;
	double	top_pixel;

	data->ray->dist *= cos(normalize_angle(data->ray->rayangle
			- data->player->angle));
    if (data->ray->dist == 0)
        data->ray->dist = 1;
	wall_height = (TILE / data->ray->dist) * ((data->screen_width / 2)
		/ tan(data->player->fovradian / 2));
	bottom_pixel = (data->screen_height / 2) + (wall_height / 2);
	top_pixel = (data->screen_height / 2) - (wall_height / 2);
	draw_textured_wall(data, ray, top_pixel, bottom_pixel);
	render_background(data, ray, top_pixel, bottom_pixel);
}
 