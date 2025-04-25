#include "gol.h"

void	draw_bg(data* _data, uint32_t color) {
	/*for (int y = 0; y < _data->height; y++) 
		for (int x = 0; x < _data->width; x++)
			mlx_put_pixel(_data->mlx_img, x, y, color);*/
	SDL_SetRenderDrawColor(_data->renderer,
			(color >> 24) & 0xFF,
			(color >> 16) & 0xFF,
			(color >> 8) & 0xFF,
			0xFF);

	SDL_RenderClear(_data->renderer);
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

	/*mlx_image_t *image = mlx_put_string(_data->mlx_ptr, num_str, x, y);
	if (image) {
		//mlx_image_to_window(_data->mlx_ptr, image, x, y);
		if (_data->number_imgs[index])
			mlx_delete_image(_data->mlx_ptr, _data->number_imgs[index]);
		_data->number_imgs[index] = image;
	}
	else	_data->number_imgs[index] = NULL;*/
}

void	draw_info(data* _data) {
	int		width = 250,
			height = 90;

	/*for (int y  = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			mlx_put_pixel(_data->mlx_img, x, y, 0x000000FF);*/

	put_number(_data, _data->_world->generation, 110, 5, 0);
	put_number(_data, _data->_world->current_population, 110, 22, 1);
	put_number(_data, _data->PPC, 180, 39, 2);
	put_number(_data, _data->FPG, 230, 56, 3);
}

void	draw_population(data *_data) {
	int		margin_x = _data->_world->columns / (2 * _data->PPC),
			margin_y = _data->_world->rows / (2 * _data->PPC);
	int		row = _data->_world->center_y - margin_y, column;

	int		max_points = _data->_world->current_population * _data->PPC;

	SDL_FPoint	points[max_points];

	int	Index = 0;

	SDL_SetRenderDrawColor(_data->renderer, (CELL_COLOR >> 24) & 0xFF,
			(CELL_COLOR >> 16) & 0xFF,
			(CELL_COLOR >> 8) & 0xFF,
			0xFF);

	for (int y = 0; y < _data->height && Index < max_points; y++) {
		column = _data->_world->center_x - margin_x;
		if (y && !(y % _data->PPC)) row += 1;
		if (row >= _data->_world->rows || row > _data->_world->center_y + margin_y || row < 0) break ;
		for (int x = 0; x < _data->width && Index < max_points; x++) {
			if (x && !(x % _data->PPC))	column += 1;
			if (column >= _data->_world->columns || column > _data->_world->center_x + margin_x || column < 0) break;
			//if (_data->_world->population[row][column]) mlx_put_pixel(_data->mlx_img, x, y, CELL_COLOR << 8 | 0xFF);
			if (_data->_world->population[row][column]) {
				points[Index].x = x;
				points[Index++].y = y;
			}
		}
	}
	SDL_RenderPoints(_data->renderer, points, Index);
	//draw_info(_data);
}
