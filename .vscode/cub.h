/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamsingh <kamsingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:12:34 by ashirzad          #+#    #+#             */
/*   Updated: 2024/08/01 13:10:59 by kamsingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include "libft/libft.h"
#include "lib/MLX42/include/MLX42/MLX42.h"

#define TILE 30
#define FOV 60
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define TILE 30

typedef struct s_parse {
    int    north;
    int    south;
    int    west;
    int    east;
    int    floor;
    int    ceiling;
}   t_parse;

typedef struct s_info {
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    char    *sprite;
    char    *floor;
    char    *ceiling;
    char    **map;
}   t_info;

typedef struct s_hero {
    int     x;
    int     y;
    double  angle;
    int     rotated; 
    int     lefty_righty;
    int     down_up; 
    int     fr;
    double  fov;
}   t_hero;

typedef struct s_field {
    int     hero_x;
    int     hero_y;
    int     height;
    int     width;
	int    f_rgb;
	int    c_rgb;
	int		hero_dir;
	double  ray_ngl;    
    double  distance;   
    int     flag;        
	int color;
	double  fov;
	   mlx_image_t *texture;
}   t_field;

typedef struct s_texture {
	mlx_texture_t *image;
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *west;
    mlx_texture_t *east;
	int height;
}   t_texture;

typedef struct s_game {
    t_hero    *hero;
    t_field   *field;
    mlx_image_t    *img;
    t_info  *info;
    t_texture *textures;
    mlx_t     *mlx; // MLX pointer
}   t_game;

//check file
int     check_file(char **tab);

//map
char    **ft_map(char **tab);

//utils.c
int     list_len(char **list);
int     what_isit(char *str);
t_info  *map_info(char **tab);
int     ft_isit(char *str);
void    free_list(char **tab);
int     ft_rgba(char **argv);
void    ft_listcpy(char **dst, char **src);
int     map_length(char **tab);

// check_map.c
int     check_map(char **tab);

//ft_parse
t_info  *ft_parse(char **tab);

//player_handler
int		pos_check(t_game *game, double y, double x);
void	rotate_cal(t_game *game, int direction);
void	move_cal(t_game *data, double *movex, double *movey);
void	handle_player(t_game *data);

//rendering.c
int			is_outside_screen(int x, int y, int screen_width, int screen_height):
void		set_pixel(t_game *data, int x, int y, int color);
void		render_background(t_game *data, int ray
			, int top_pixel, int bottom_pixel);
void		determine_texture(t_game *data);
void		render_ray(t_game *data, int ray);

//sic-raycast.c
float	get_horizontal_distance_to_wall(t_game *game, double ray_angle);
float	get_vertical_distance_to_wall(t_game *game, double ray_angle);
void	render_rays(t_game *game);
int		is_point_inside_map_bounds(t_game *game, float x, float y);
int		calculate_intersection_step(double ray_angle,
		float *intersection, float *step, int flag);
int	is_point_on_wall(t_game *game, float x, float y);
float	normalize_angle(float angle);

//main_help.c
void	game_loop(void *param);
void	start_the_game(t_game *game)
void	init_textures(t_game *game);
void	ft_hook_one(mlx_key_data_t keydata, void *param);