#ifndef	GOL_H
# define	GOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <SDL3/SDL.h>

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
#define	CELL_COLOR	0xF0EEE9FF

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
	/*mlx_image_t	*text_img;
	mlx_image_t	*number_imgs[4];*/
	SDL_Window	*win;
	SDL_Renderer	*renderer;
	//
	int		width;
	int		height;
	world_data	*_world;
	mouse_data	*_mouse;
	int		PPC;
	int		FPG;
	//
	int		cur_frame;
	int		last_resize_w;
	int		last_resize_h;
	//
	FILE		*input;
	//
}	data;

void	build_population(data *, bool);
void	updata_population(data *);
void	free_population(bool **, int);

int	release(data*, int);
int	__calc_new_range(int, int, int, int, int);
int	rand_num(int, int);

void	resize_handle(data*);
void	key_handle(data*, SDL_Event*);
void	mouse_wheel_handle(data*, SDL_Event*);

/*
void	wheel_handle(data*, SDL_Event*);
void	mouse_key_handle(data*, SDL_Event*, int);
void	mouse_motion_handle(data*, SDL_Event*);
*/

void	insert_seed(data *, char **);

void	draw_population(data *);
void	draw_bg(data *, uint32_t);
void	put_number(data *, int, int, int ,int);
void	draw_info(data *);

#endif
