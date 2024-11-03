#ifndef	GOF_H
# define	GOF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include "MLX42.h"

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

#define	DEF_PPC		1
#define	DEF_FPG		4
#define	MIN_WIDTH		600
#define	MIN_HEIGHT	300
#define	DEF_WIDTH		1600
#define	DEF_HEIGHT	800
#define	BG_COLOR		0x151515
#define	CELL_COLOR	0xF0EEE9

typedef struct mouse_data
{
	int		init_cursor_x;
	int		init_cursor_y;
	bool		cursor_pressed;
}	mouse_data;

typedef struct map_data
{
	bool		**population;
	int		generation;
	int		current_population;
	int		rows;
	int		columns;
	int		center_x;
	int		center_y;
}	world_data;

typedef struct data
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*mlx_img;
	mlx_image_t	*text_img;
	mlx_image_t	*number_imgs[4];
	int		width;
	int		height;
	world_data	*_world;
	mouse_data	*_mouse;
	int		PPC;
	int		FPG;
	int		cur_frame;
	//
	FILE		*input;
	//
}	data;

void	build_population(data *, bool);
void	updata_population(data *);
void	free_population(world_data *);

int	release(data*, int);
int	__calc_new_range(int, int, int, int, int);
int	rand_num(int, int);

void	close_handle(void *);
void	resize_handle(int, int, void *);
void	key_handle(mlx_key_data_t, void *);
void	scroll_handle(double, double, void *);
void	mouse_handle(mouse_key_t, action_t, modifier_key_t, void*);
void	cursor_handle(double, double, void*);

void	insert_seed(data *, char **);

void	draw_population(data *);
void	draw_bg(data *, int);
void	put_number(data *, int, int, int ,int);
void	draw_info(data *);

#endif
