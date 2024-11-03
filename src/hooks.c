#include "gof.h"

void	close_handle(void *p) {
	data	*_data = (data*)p;
	exit( release(_data, 0) );
}

void	resize_handle(int w, int h, void *p) {
	if (h > MIN_HEIGHT && w > MIN_WIDTH) { 
		data	*_data = (data*)p;
		_data->height = h;
		_data->width = w;
		if (!mlx_resize_image(_data->mlx_img, _data->width, _data->height))
			exit( release(_data, 1) );
	}
}

void	key_handle(mlx_key_data_t keydata, void *p) {
	if (keydata.action == MLX_RELEASE)	return;

	data	*_data = (data*)p;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_handle(p);
	else if (keydata.key == MLX_KEY_UP && _data->FPG < 100)
		_data->FPG += 1;
	else if (keydata.key == MLX_KEY_DOWN && _data->FPG > 1)
		_data->FPG -= 1;
}

void	scroll_handle(double xdelta, double ydelta, void *param) {
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
		diff_x = (_data->_mouse->init_cursor_x - (int)xpos) / 10;
		diff_y = (_data->_mouse->init_cursor_y - (int)ypos) / 10;

		margin_y = _data->_world->rows / (2 * _data->PPC);
		margin_x = _data->_world->columns / (2 * _data->PPC);
		
		new_center_x = _data->_world->center_x + diff_x/_data->PPC;
		new_center_y = _data->_world->center_y + diff_y/_data->PPC;
		
		if (new_center_x - margin_x > 0 && new_center_x + margin_x < _data->_world->columns)
			_data->_world->center_x = new_center_x;
		if (new_center_y - margin_y > 0 && new_center_y + margin_y < _data->_world->rows)
			_data->_world->center_y = new_center_y;
	}
}