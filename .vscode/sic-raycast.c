/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sic-raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamsingh <kamsingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:19:04 by kamsingh          #+#    #+#             */
/*   Updated: 2024/08/01 12:50:15 by kamsingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	get_horizontal_distance_to_wall(t_game *game, double ray_angle)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	distance;
	int tile_x;
	int tile_y;

	x = game->field->hero_x;
	y = game->field->hero_y;
	dx = cos(ray_angle);
	dy = sin(ray_angle);
	distance = 0;
	while (1)
	{
		x += dx * TILE;
		y += dy * TILE;
		tile_x = (int)x / TILE;
		tile_y = (int)y / TILE;
		if (tile_x < 0 || tile_x >= SCREEN_WIDTH
			|| tile_y < 0 || tile_y >= SCREEN_HEIGHT)
						break;
		if (game->info->map[tile_y][tile_x] == 1)
		{
			distance = sqrt(pow(x - game->field->hero_x, 2)
					+ pow(y - game->field->hero_y, 2));
			break ;
		}
	}
	return (distance);
}

float	get_vertical_distance_to_wall(t_game *game, double ray_angle)
{
	float	intersection;
	float	step;
	int		pixel;
	float	x;
	float	y;

	if (ray_angle > M_PI)
	{
		intersection = floor(game->field->hero_x / TILE) * TILE - TILE;
		step = -TILE;
	}
	else
	{
		intersection = floor(game->field->hero_x / TILE) * TILE + TILE;
		step = TILE;
	}
	pixel = inter_check(ray_angle, &intersection, &step, 0);
	if (pixel == -1)
		return (1);
	x = game->field->hero_x;
	y = game->field->hero_y + (intersection - game->field->hero_x)
		* tan(ray_angle);
	while (is_point_within_map(game, x, y) &&!is_point_wall(game, x, y))
	{
		x += step;
		y += step * tan(ray_angle);
	}
	return (sqrt(pow(x - game->field->hero_x, 2)
			+ pow(y - game->field->hero_y, 2)));
}

void render_rays(t_game *game)
{
	int		ray;
	double	ray_angle;
	float	vertical_distance;
	float	horizontal_distance;

	ray = 0;
	ray_angle = nor_angle(game->field->ray_ngl - game->field->fov / 2);
	while (ray < 1024)
	{
		game->field->flag = 0;
		horizontal_distance = find_horizontal_intersection(game, ray_angle);
		vertical_distance = find_vertical_intersection(game, ray_angle);
		if (vertical_distance <= horizontal_distance)
			game->field->distance = vertical_distance;
		else
		{
			game->field->distance = horizontal_distance;
			game->field->flag = 1;
		}
		// render(game, ray);
		ray++;
		ray_angle += game->field->fov / 1024;
	}
}

int	is_point_inside_map_bounds(t_game *game, float x, float y)
{
	int	tile_x;
	int	tile_y;
	(void)game;

	tile_x = (int)x / TILE;
	tile_y = (int)y / TILE;
	if (tile_x < 0 || tile_x >= SCREEN_WIDTH
		|| tile_y < 0 || tile_y >= SCREEN_HEIGHT)
		return (0);
	return (1);
}

int	calculate_intersection_step(double ray_angle,
		float *intersection, float *step, int flag)
{
	(void)flag;
	if (ray_angle > M_PI)
	{
		*intersection = floor(*intersection / TILE) * TILE - TILE;
		*step = -TILE;
	}
	else
	{
		*intersection = floor(*intersection / TILE) * TILE + TILE;
		*step = TILE;
	}
	return (0);
}

int	is_point_on_wall(t_game *game, float x, float y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)x / TILE;
	tile_y = (int)y / TILE;
	if (game->info->map[tile_y][tile_x] == 1)
		return (1);
	return (0);
}

float	normalize_angle(float angle)
{
	angle = angle - (int)(angle / (2 * M_PI)) * 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}


// Here's a detailed explanation of each function:

// 1. unit_circle function

// This function takes two parameters: angle (a float representing an angle in radians)
//  and c (a character, either 'x' or 'y'). It returns an integer value (0 or 1).

// The function checks if the angle falls within a specific quadrant of the unit circle:

// If c is 'x', it checks if the angle is between 0 and π (i.e., the right half of the unit
//  circle). If true, it returns 1.
// If c is 'y', it checks if the angle is between π/2 and 3π/2 (i.e., the top half of 
// the unit circle). If true, it returns 1.
// Otherwise, it returns 0.

// 2. inter_check function

// This function takes four parameters: angle (a float representing an angle in radians),
//  inter (a pointer to a float), step (a pointer to a float), and is_horizon (an integer, 
//  either 0 or 1). It returns an integer value (1 or -1).

// The function checks the angle and updates the inter and step values accordingly:

// If is_horizon is 1, it checks if the angle is between 0 and π. If true, it sets inter
//  to inter + TILE and returns -1. Otherwise, it sets step to -step and returns 1.
// If is_horizon is 0, it checks if the angle is not between π/2 and 3π/2. If true, i
// t sets inter to inter + TILE and returns -1. Otherwise, it sets step to -step and returns 1.
// 3. raycast function

// This function takes a t_game pointer as a parameter. It performs a raycasting
//  algorithm to render a 2D scene.

// Here's a high-level overview of what the function does:

// It initializes a loop that will iterate 1024 times (i.e., for each ray in the scene).
// For each ray, it calculates the horizontal and vertical intersection distances
//  using the findHorizontalIntersection and findVerticalIntersection functions.
// It sets the distance and flag values for the current ray based on the intersection 
// distances.
// It increments the ray angle by a small amount (game->hero->fr / 1024) and repeats 
// the process for the next ray.
// 4. wall_hit function

// This function takes three parameters: x and y (floats representing coordinates) 
// and a t_game pointer. It returns an integer value (0 or 1).

// The function checks if the point (x, y) is within the bounds of the game map and 
// if the corresponding map cell is a wall (i.e., its value is '1'). If both conditions 
// are true, it returns 1. Otherwise, it returns 0.

// 5. findHorizontalIntersection function

// This function takes a t_game pointer and a rayAngle (a double representing an angle 
// in radians) as parameters. It returns a float value representing the distance to the
//  horizontal intersection point.

// Here's a high-level overview of what the function does:

// It initializes the inter and step values based on the rayAngle.
// It calls the inter_check function to update the inter and step values.
// It calculates the x and y coordinates of the intersection point using the inter
//  and step values.
// It checks if the intersection point is within a wall using the wall_hit function. 
// If not, it increments the x and y coordinates by step and repeats the process until 
// it finds a wall.
// It returns the distance from the hero's position to the intersection point.
// 6. findVerticalIntersection function

// This function is similar to findHorizontalIntersection, but it calculates 
// the vertical intersection distance instead.

// 7. nor_angle function

// This function takes a angle (a double representing an angle in radians) 
// as a parameter. It returns a normalized angle value between 0 and 2π.

// The function uses the fmod function to reduce the angle to its equivalent
//  value within the range [0, 2π). If the resulting angle is negative, it adds 2π
//  to get a positive value within the range [0, 2π).