#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
	int		FPG;
	int		cur_frame;
	int		rows;
	int		columns;
	//
	int		center_x;
	int		center_y;
	//
	int		init_cursor_x;
	int		init_cursor_y;
	int		cursor_pressed;
	//
	FILE		*input;
	int		initial_seed_w;
	int		initial_seed_h;
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
		for (int x = 0; x < _data->width; x++)
			mlx_put_pixel(_data->mlx_img, x, y, color);
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
	if (keydata.action == MLX_RELEASE)	return;

	if (keydata.key == MLX_KEY_ESCAPE)
		close_handle(p);
}

void	scroll_handle(double xdelta, double ydelta, void *param) {
	data	*_data = (data*)param;

	if (ydelta > 0 && _data->PPC < _data->width && _data->PPC < _data->height) 
		_data->PPC += 1;
	else if (ydelta < 0 && _data->PPC > 1) 
		_data->PPC -= 1;
	if (_data->PPC == 1) {
		_data->center_x = _data->columns / 2;
		_data->center_y = _data->rows / 2;
	}
}

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void *param) {
	data	*_data = (data*)param;
	///
	if (!_data->cursor_pressed && action == MLX_PRESS)
		_data->cursor_pressed = 1;
	else if (_data->cursor_pressed && action == MLX_RELEASE) 
		_data->cursor_pressed = 0;
}
//
int	__calc_new_range(int old_value, int old_min, int old_max, int new_min, int new_max) {
	if (old_value == old_min)
		return(new_min);
	return (((old_value - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min;
}

void	cursor_handle(double xpos, double ypos, void *param) {
	data	*_data = (data*)param;
	int	diff_x, diff_y,
		new_center_x, new_center_y,
		margin_x, margin_y;
	//	
	if (!_data->cursor_pressed) {
		_data->init_cursor_x = xpos;
		_data->init_cursor_y = ypos;
	}
	else {
		diff_x = (_data->init_cursor_x - (int)xpos) / 10;
		diff_y = (_data->init_cursor_y - (int)ypos) / 10;

		margin_y = _data->rows / (2 * _data->PPC);
		margin_x = _data->columns / (2 * _data->PPC);
		
		new_center_x = _data->center_x + diff_x/_data->PPC;
		new_center_y = _data->center_y + diff_y/_data->PPC;
		
		if (new_center_x - margin_x > 0 && new_center_x + margin_x < _data->columns)
			_data->center_x = new_center_x;
		if (new_center_y - margin_y > 0 && new_center_y + margin_y < _data->rows)
			_data->center_y = new_center_y;
	}
}

void	updata_population(data *_data) {
	//	game-of-life rules
	int	live_neighbors, c_row, c_column;
	int	temp_population[_data->rows][_data->columns];
	memset(temp_population, FALSE, _data->columns * _data->rows);

	_data->generation += 1;
	_data->current_population = 0;
	for (int row = 0; row < _data->rows; row++)
		for (int column = 0; column < _data->columns; column++) {
			live_neighbors = 0;

			c_row = row;
			c_column = column + 1;
			if (c_column >= _data->columns)
				c_column = 0;
			live_neighbors += _data->population[c_row][c_column];

			c_row = row + 1;
			if (c_row >= _data->rows) 
				c_row = 0;
			live_neighbors += _data->population[c_row][c_column];

			c_row = row - 1;
			if (c_row < 0)
				c_row = _data->rows - 1;
			live_neighbors += _data->population[c_row][c_column];
			
			c_row = row;	
			c_column = column - 1;
			if (c_column < 0)
				c_column = _data->columns - 1;
			live_neighbors += _data->population[row][c_column];

			c_row = row + 1;
			if (c_row >= _data->rows) 
				c_row = 0;
			live_neighbors += _data->population[c_row][c_column];

			c_row = row - 1;
			if (c_row < 0)
				c_row = _data->rows - 1;
			live_neighbors += _data->population[c_row][c_column];

			c_column = column;
			c_row = row + 1;
			if (c_row >= _data->rows)
				c_row = 0;
			live_neighbors += _data->population[c_row][c_column];

			c_row = row - 1;
			if (c_row < 0)
				c_row = _data->rows - 1;
			live_neighbors += _data->population[c_row][c_column];
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
		//mlx_image_to_window(_data->mlx_ptr, image, x, y);
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
	put_number(_data, _data->FPG, 230, 56, 3);
}

void	draw_population(data *_data) {
	int		margin_x = _data->columns / (2 * _data->PPC),
			margin_y = _data->rows / (2 * _data->PPC);
	int		row = _data->center_y - margin_y, column;

	for (int y = 0; y < _data->height; y++) {
		column = _data->center_x - margin_x;
		if (y && !(y % _data->PPC)) row += 1;
		if (row >= _data->rows || row > _data->center_y + margin_y || row < 0) break ;
		for (int x = 0; x < _data->width; x++) {
			if (x && !(x % _data->PPC))	column += 1;
			if (column >= _data->columns || column > _data->center_x + margin_x || column < 0) break;
			if (_data->population[row][column]) mlx_put_pixel(_data->mlx_img, x, y, 0xDEDEDEFF);
		}
	}
	draw_info(_data);
}

void	loop_hook(void *p) {
	data	*_data = (data*)p;
	//
	if (_data->cur_frame >= _data->FPG) {
		_data->cur_frame = 0;
		draw_bg(_data, 0x1C1C1CFF);
		updata_population(_data);
		draw_population(_data);
	}
	else	_data->cur_frame += 1;
}

int	rand_num(int min, int max) {
	return	rand() % (max - min + 1) + min;
}

void	build_population(data *_data, bool seed) {
	_data->population = malloc( (_data->rows + 1) * sizeof(bool*) );
	if (!_data->population)
		exit( release(_data, 1) );
	for (int y = 0; y < _data->rows; y++) {
		_data->population[y] = malloc( _data->columns * sizeof(bool) );
		if (!_data->population[y]) exit( release(_data, 1) );
		//
		if (!seed)
			for (int x = 0; x < _data->columns; x++)
				_data->population[y][x] = rand_num(FALSE, TRUE);
		else	memset(_data->population[y], FALSE, sizeof(bool) * _data->columns);
	}
	_data->population[ _data->rows ] = NULL;
}

void	insert_seed(data *_data) {
	int	x = (_data->columns - _data->initial_seed_w) / 2,
		y = (_data->rows - _data->initial_seed_h) / 2;

	if (x >= 0 && y >= 0 && x <= _data->columns && y <= _data->rows) {
		int		read;
		bool		valid;
		size_t		size = 1024;
		char		*buffer = malloc(size);
		if (buffer) {
			while ((read = getline(&buffer, &size, _data->input)) > 0) {
				valid = TRUE;
				for (int i = 0; i < read; i++) {
					if (buffer[i] == '#' || buffer[i] == 'x' || buffer[i] == 'y') {
						valid = FALSE;
						break;
					}
				}
				if (!valid)	continue;
				printf("%s", buffer);
			}
			free(buffer);
		}
	}
	fclose(_data->input);
}

void	check_seed(data *_data, char **v) {
	_data->input = fopen(v[1], "r");
	
	if (!_data->input)
		return;

	int		read;
	int		w, h, x, y;
	size_t		size = 1024;
	char		*buffer = malloc(size);

	if (!buffer) {
		fclose(_data->input);
		return;
	}
	
	while ((read = getline(&buffer, &size, _data->input)) > 0) {
		w = 0;
		h = 0;
		for (int i = 0; i < read; i++){
			if (buffer[i] == '#') 
				break;
			else if (buffer[i] == 'x') {
				while (i < read && buffer[i] != ',' && buffer[i] != '\n') {
					if (isdigit(buffer[i]))
						w = w * 10 + ( buffer[i] - '0' );
					i++;
				}
				if (!w || w > _data->columns) {
					fclose(_data->input);
					free(buffer);
					return;
				}
				_data->initial_seed_w = w;
				x = (_data->columns - _data->initial_seed_w) / 2;
			}
			else if (buffer[i] == 'y') {
				while (i < read && buffer[i] != ',' && buffer[i] != '\n') {
					if (isdigit(buffer[i]))
						h = h * 10 + ( buffer[i] - '0' );
					i++;
				}
				if (!h || h > _data->columns) {
					fclose(_data->input);
					free(buffer);
					return;
				}
				_data->initial_seed_h = h;
				y = (_data->rows - _data->initial_seed_h) / 2;
			}
		}

	}
	fclose(_data->input);
	free(buffer);
}

void	init_world(data *_data, char **v) {
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

	build_population(_data, v ? TRUE : FALSE);
	if (v) insert_seed(_data);
}

int			main(int c, char **v) {
	if (c > 2)	return 1;

	data	*_data = malloc(sizeof(data));
	if (!_data)
		return 1;

	memset(_data, 0, sizeof(data));
	_data->width = 1600;
	_data->height = 800;

	_data->mlx_ptr = mlx_init(_data->width, _data->height, c == 2 ? v[1] : "Game of life", true);
	if (!_data->mlx_ptr)
		return	release(_data, 1);

	_data->mlx_img = mlx_new_image(_data->mlx_ptr, _data->width, _data->height);
	if (!_data->mlx_img)
		return	release(_data, 1);

	_data->PPC = 1;
	draw_bg(_data, 0x000000FF);

	_data->center_x = (_data->width / 2) * _data->PPC;
	_data->center_y = (_data->height / 2) * _data->PPC;
	
	mlx_image_to_window(_data->mlx_ptr, _data->mlx_img, 0, 0);
	mlx_close_hook(_data->mlx_ptr, close_handle, _data);
	mlx_key_hook(_data->mlx_ptr, key_handle, _data);
	mlx_resize_hook(_data->mlx_ptr, resize_handle, _data);
	mlx_scroll_hook(_data->mlx_ptr, scroll_handle, _data);
	mlx_cursor_hook(_data->mlx_ptr, cursor_handle, _data);
	mlx_mouse_hook(_data->mlx_ptr, mouse_handle, _data);

	_data->FPG = 1;
	_data->rows = _data->height / _data->PPC;
	_data->columns = _data->width / _data->PPC;

	init_world(_data, c == 2 ? v : NULL);

	mlx_loop_hook(_data->mlx_ptr, loop_hook, _data);
	mlx_loop(_data->mlx_ptr);
}
