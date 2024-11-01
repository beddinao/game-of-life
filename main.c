#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./MLX42/include/MLX42/MLX42.h"

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

typedef struct data
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*mlx_img;
	mlx_image_t	*text_img;
	mlx_image_t	*number_imgs[4];
	int		width;
	int		height;
	int		PPC;
	int		GPF;
	int		cur_frame;
	int		rows;
	int		columns;
	//
	bool		**population;
	int		generation;
	int		current_population;
}	data;

void	free_population(data *_data) {
	for (int y = 0; _data->population[y] && y < _data->rows; y++) 
		free(_data->population[y]);
	free(_data->population);
	_data->population = NULL;
}

int	release(data *_data, int status) {

	if (!_data)
		return status;

	if (_data->mlx_ptr && _data->mlx_img)
		mlx_delete_image(_data->mlx_ptr, _data->mlx_img);

	if (_data->mlx_ptr && _data->text_img)
		mlx_delete_image(_data->mlx_ptr, _data->text_img);

	if (_data->mlx_ptr)
		for (int i = 0; i < 4; i++)
			if (_data->number_imgs[i]) mlx_delete_image(_data->mlx_ptr, _data->number_imgs[i]);

	if (_data->mlx_ptr)
		mlx_terminate(_data->mlx_ptr);

	if (_data->population)
		free_population(_data);
	
	free(_data);

	return	status;
}

void	draw_bg(data* _data, int color) {
	for (int y = 0; y < _data->height; y++) 
		for (int x = 0; x < _data->width; x++) {
			mlx_put_pixel(_data->mlx_img, x, y, color);
		}
}

void	close_handle(void *p) {
	data	*_data = (data*)p;
	exit( release(_data, 0) );
}

void	resize_handle(int w, int h, void *p) {
	data	*_data = (data*)p;
	_data->height = h;
	_data->width = w;
	if (!mlx_resize_image(_data->mlx_img, _data->width, _data->height))
		exit( release(_data, 1) );
}

void	key_handle(mlx_key_data_t keydata, void *p) {
	if (keydata.action != MLX_PRESS)	return;

	if (keydata.key == MLX_KEY_ESCAPE)
		close_handle(p);
}

void	updata_population(data *_data) {
	//	game-of-life rules
	int	live_neighbors;
	int	temp_population[_data->rows][_data->columns];
	memset(temp_population, FALSE, _data->columns * _data->rows);

	_data->generation += 1;
	_data->current_population = 0;
	for (int row = 0; row < _data->rows; row++)
		for (int column = 0; column < _data->columns; column++) {
			live_neighbors = 0;

			if (column < _data->columns - 1) {
				live_neighbors += _data->population[row][column + 1];
				if (row < _data->rows - 1) 
					live_neighbors += _data->population[row + 1][column + 1];
				if (row)
					live_neighbors += _data->population[row - 1][column + 1];
			}

			if (column) {
				live_neighbors += _data->population[row][column - 1];
				if (row < _data->rows - 1) 
					live_neighbors += _data->population[row + 1][column - 1];
				if (row) 
					live_neighbors += _data->population[row - 1][column - 1];

			}

			if (row < _data->rows - 1) 
				live_neighbors += _data->population[row + 1][column];
			if (row) 
				live_neighbors += _data->population[row - 1][column];
			//
			if (_data->population[row][column]) {
				if (live_neighbors < 2) // underpopulation
					temp_population[row][column] = FALSE;
				else if (live_neighbors > 3) // overpopulation
					temp_population[row][column] = FALSE;
				else	temp_population[row][column] = TRUE;
			}
			else if (!_data->population[row][column] && live_neighbors == 3)
				temp_population[row][column] = TRUE;
			else	temp_population[row][column] = _data->population[row][column];
			//
			_data->current_population += temp_population[row][column];
		}

	for (int row = 0; row < _data->rows; row++)
		for (int column = 0; column < _data->columns; column++)
			_data->population[row][column] = temp_population[row][column];
}

void	put_number(data *_data, int num, int x, int y, int index) {
	int	num_size = 0, temp_num = num;

	while (temp_num) {
		num_size += 1;
		temp_num /= 10;
	}
	char	num_str[num_size + 1];
	memset(num_str, 0, num_size + 1);

	for (int i = num_size - 1; num; i--) {
		num_str[i] = (num % 10) + 48;
		num /= 10;
	}
	
	mlx_image_t *image = mlx_put_string(_data->mlx_ptr, num_str, x, y);
	if (image) {
		mlx_image_to_window(_data->mlx_ptr, image, x, y);

		if (_data->number_imgs[index])
			mlx_delete_image(_data->mlx_ptr, _data->number_imgs[index]);

		_data->number_imgs[index] = image;
	}
	else	_data->number_imgs[index] = NULL;
}

void	draw_info(data* _data) {
	int		width = 250,
			height = 90;

	for (int y  = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			mlx_put_pixel(_data->mlx_img, x, y, 0x000000FF);

	put_number(_data, _data->generation, 110, 5, 0);
	put_number(_data, _data->current_population, 110, 22, 1);
	put_number(_data, _data->PPC, 180, 39, 2);
	put_number(_data, _data->GPF, 230, 56, 3);
}

void	draw_population(data *_data) {
	int		row = 0, column;
	for (int y = 0; y < _data->height; y++) {
		if (y && !(y % _data->PPC)) row += 1;
		column = 0;
		for (int x = 0; x < _data->width; x++) {
			if (x && !(x % _data->PPC))	column += 1;
			mlx_put_pixel(_data->mlx_img, x, y, _data->population[row][column] ? 0xFFFFFFFF : 0x000000FF);
		}
	}
	draw_info(_data);
}

void	loop_hook(void *p) {
	data	*_data = (data*)p;
	//
	if (_data->cur_frame >= _data->GPF) {
		_data->cur_frame = 0;
		draw_bg(_data, 0x000000FF);
		updata_population(_data);
		draw_population(_data);
	}
	else	_data->cur_frame += 1;
}

int	rand_num(int min, int max) {
	return	rand() % (max - min + 1) + min;
}

void	build_population(data *_data) {
	_data->population = malloc( (_data->rows + 1) * sizeof(bool*) );
	if (!_data->population)
		exit( release(_data, 1) );
	for (int y = 0; y < _data->rows; y++) {
		_data->population[y] = malloc( _data->columns * sizeof(bool) );
		if (!_data->population[y]) exit( release(_data, 1) );
		/*int		start = rand_num(0, _data->columns / 3);
		int		end = rand_num(_data->columns / 2, _data->columns);
		memset(_data->population[y] + start, rand_num(FALSE, TRUE), (end-start) * sizeof(bool));*/
		memset(_data->population[y], FALSE, _data->columns * sizeof(bool));
	}
	_data->population[ _data->rows ] = NULL;
	
	int		h_height = _data->rows / 2;
	int		h_width = _data->columns / 2;

	_data->population[ h_height ][ h_width ] = TRUE;
	_data->population[ h_height - 1 ][ h_width ] = TRUE;
	_data->population[ h_height + 1 ][ h_width ] = TRUE;
	_data->population[ h_height ][ h_width - 1 ] = TRUE;
	_data->population[ h_height + 1 ][ h_width + 1 ] = TRUE;
}

void	init_world(data *_data) {
	if (!_data)	return;
	
	srand(time(NULL));
	mlx_texture_t *text = mlx_load_png("./text.png");
	if (text) {
		_data->text_img = mlx_texture_to_image(_data->mlx_ptr, text);
		if (_data->text_img)
			mlx_image_to_window(_data->mlx_ptr, _data->text_img, 10, 10);
		mlx_delete_texture(text);
	}
	else	_data->text_img = NULL;

	for (int i = 0; i < 4; i++)
		_data->number_imgs[i] = NULL;
	//
	build_population(_data);
	//	customizations;
	/*printf("init_world: height: %i, width: %i, PPC: %i, rows: %i, columns: %i\n",
		_data->height, _data->width, _data->PPC, _data->rows, _data->columns);*/
}

int			main() {
	data	*_data = malloc(sizeof(data));
	if (!_data)
		return 1;

	memset(_data, 0, sizeof(data));
	_data->width = 1600;
	_data->height = 800;
	_data->mlx_ptr = mlx_init(_data->width, _data->height, "Game of life", true);
	if (!_data->mlx_ptr)
		return	release(_data, 1);
	_data->mlx_img = mlx_new_image(_data->mlx_ptr, _data->width, _data->height);
	if (!_data->mlx_img)
		return	release(_data, 1);

	_data->PPC = 4;
	draw_bg(_data, 0x000000FF);
	
	mlx_image_to_window(_data->mlx_ptr, _data->mlx_img, 0, 0);
	mlx_close_hook(_data->mlx_ptr, close_handle, _data);
	mlx_key_hook(_data->mlx_ptr, key_handle, _data);
	mlx_resize_hook(_data->mlx_ptr, resize_handle, _data);

	_data->GPF = 4;
	_data->rows = _data->height / _data->PPC;
	_data->columns = _data->width / _data->PPC;
	init_world(_data);

	mlx_loop_hook(_data->mlx_ptr, loop_hook, _data);
	mlx_loop(_data->mlx_ptr);
}
