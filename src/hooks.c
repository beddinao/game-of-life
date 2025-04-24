#include "gol.h"

void	move_population(bool **dest, bool **src, data *_data, int src_rows, int src_columns) {
	for (int y = 0; y < _data->_world->rows && y < src_rows; y++)
		for (int x = 0; x < _data->_world->columns && x < src_columns; x++)
			dest[y][x] = src[y][x];
}

void	resize_handle(data* _data) {
	int	w, h;

	if (!SDL_GetWindowSize(_data->win, &w, &h))
		return;

	if (h > MIN_HEIGHT && w > MIN_WIDTH
		&& h < INT_MAX && w < INT_MAX) {
		_data->height = h;
		_data->width = w;
		//
		if (abs(h - _data->last_resize_h) > 30 && abs(w - _data->last_resize_w) > 30) {
			bool	**old_population = _data->_world->population;
			int	old_rows = _data->_world->rows,
				old_columns = _data->_world->columns;
			
			_data->_world->columns = w / _data->PPC;
			_data->_world->rows = h / _data->PPC;
			_data->_world->center_x = (w / 2) * _data->PPC;
			_data->_world->center_y = (h / 2) * _data->PPC;
			//
			build_population(_data, TRUE);
			move_population(_data->_world->population, old_population,
				_data, old_rows, old_columns);
			free_population(old_population, old_rows);
			//
			_data->last_resize_w = w;
			_data->last_resize_h = h;
		}
	}
}

void	key_handle(data *_data, SDL_Event *event) {
	SDL_Keycode key = event->key.key;

	if (key == SDLK_ESCAPE)
		exit( release(_data, 0) );	
	else if (key == SDLK_UP && _data->FPG < 100)
		_data->FPG += 1;
	else if (key == SDLK_DOWN && _data->FPG > 1)
		_data->FPG -= 1;
}

/*void	scroll_handle(double xdelta, double ydelta, void *param) {
	data	*_data = (data*)param;

	if (ydelta > 0 && _data->PPC < _data->width && _data->PPC < _data->height) 
		_data->PPC += 1;
	else if (ydelta < 0 && _data->PPC > 1) 
		_data->PPC -= 1;
	if (_data->PPC == 1) {
		_data->_world->center_x = _data->_world->columns / 2;
		_data->_world->center_y = _data->_world->rows / 2;
	}
}

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void *param) {
	data	*_data = (data*)param;
	///
	if (!_data->_mouse->cursor_pressed && action == MLX_PRESS)
		_data->_mouse->cursor_pressed = 1;
	else if (_data->_mouse->cursor_pressed && action == MLX_RELEASE) 
		_data->_mouse->cursor_pressed = 0;
}

void	cursor_handle(double xpos, double ypos, void *param) {
	data	*_data = (data*)param;
	int	diff_x, diff_y,
		new_center_x, new_center_y,
		margin_x, margin_y;
	//	
	if (!_data->_mouse->cursor_pressed) {
		_data->_mouse->init_cursor_x = xpos;
		_data->_mouse->init_cursor_y = ypos;
	}
	else {
		diff_x = (_data->_mouse->init_cursor_x - (int)xpos) / 5;
		diff_y = (_data->_mouse->init_cursor_y - (int)ypos) / 5;

		margin_y = _data->_world->rows / (2 * _data->PPC);
		margin_x = _data->_world->columns / (2 * _data->PPC);
		
		new_center_x = _data->_world->center_x + diff_x/_data->PPC;
		new_center_y = _data->_world->center_y + diff_y/_data->PPC;
		
		if (new_center_x - margin_x > 0 && new_center_x + margin_x < _data->_world->columns)
			_data->_world->center_x = new_center_x;
		if (new_center_y - margin_y > 0 && new_center_y + margin_y < _data->_world->rows)
			_data->_world->center_y = new_center_y;
	}
}*/
