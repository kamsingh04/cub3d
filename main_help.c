/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamsingh <kamsingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:41:07 by kamsingh          #+#    #+#             */
/*   Updated: 2024/08/01 13:10:43 by kamsingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_hook_one(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_W)
		game->hero->down_up = 1;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_S)
		game->hero->down_up = -1;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_A)
		game->hero->lefty_righty = -1;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_D)
		game->hero->lefty_righty = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
		game->hero->rotated = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
		game->hero->rotated = 1;
	else if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
			game->hero->down_up = 0;
		if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
			game->hero->lefty_righty = 0;
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
			game->hero->rotated = 0;
	}
}

void	init_textures(t_game *game)
{
	game->textures->north = mlx_load_png("texture\\giappone.png");
	game->textures->south = mlx_load_png("texture\\giappone.png");
	game->textures->east = mlx_load_png("texture\\kiko.png");
	game->textures->west = mlx_load_png("texture\\pippo.png");
}

void start_the_game(t_game *game)
{
	game->hero = calloc(1, sizeof(t_hero));
	game->field = calloc(1, sizeof(t_field));
	game->textures = calloc(1, sizeof(t_texture));
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", 0);
	game->hero->x = game->field->hero_x * TILE + TILE / 2;
	game->hero->y = game->field->hero_y * TILE + TILE / 2;
	game->hero->angle = game->field->hero_dir * M_PI / 2;
	game->hero->fr = FOV * M_PI / 180;
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	init_textures(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, &ft_hook_one, game);
	mlx_loop(game->mlx);
}

void	game_loop(void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (!game->img)
	{
		printf("Failed to create image\n");
		return ;
	}
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	raycast(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}