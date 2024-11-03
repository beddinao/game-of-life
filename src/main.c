#include "gof.h"

void	free_population(world_data *_world) {
	for (int y = 0; _world->population[y] && y < _world->rows; y++) 
		free(_world->population[y]);
	free(_world->population);
	_world->population = NULL;
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

	if (_data->_world && _data->_world->population)
		free_population(_data->_world);

	if (_data->input)
		fclose(_data->input);

	if (_data->_mouse)
		free(_data->_mouse);

	if (_data->_world)
		free(_data->_world);
	
	free(_data);

	return	status;
}
//
int	__calc_new_range(int old_value, int old_min, int old_max, int new_min, int new_max) {
	if (old_value == old_min)
		return(new_min);
	return (((old_value - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min;
}

void	loop_hook(void *p) {
	data	*_data = (data*)p;
	//
	if (_data->cur_frame >= _data->FPG) {
		_data->cur_frame = 0;
		draw_bg(_data, BG_COLOR << 8 | 0xFF);
		updata_population(_data);
		draw_population(_data);
	}
	else	_data->cur_frame += 1;
}

int	rand_num(int min, int max) {
	return	rand() % (max - min + 1) + min;
}

void	init_world(data *_data, char **v) {
	if (!_data)	return;
	
	srand(time(NULL));
	mlx_texture_t *text = mlx_load_png("./images/info_text.png");
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
	if (v) insert_seed(_data, v);
}

int			main(int c, char **v) {
	if (c > 2)	return 1;

	data	*_data = malloc(sizeof(data));
	if (!_data)
		return 1;
	memset(_data, 0, sizeof(data));

	_data->_world = malloc(sizeof(world_data));
	if (!_data->_world) {
		free(_data);
		return 1;
	}
	_data->_mouse = malloc(sizeof(mouse_data));
	if (!_data->_mouse) {
		free(_data->_world);
		free(_data);
		return 1;
	}
	memset(_data->_world, 0, sizeof(world_data));
	memset(_data->_mouse, 0, sizeof(mouse_data));

	//	TODO
	signal(SIGINT, exit);
	signal(SIGILL, SIG_IGN);
	signal(SIGFPE, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, exit);
	signal(SIGSEGV, exit);
	//

	_data->width = DEF_WIDTH;
	_data->height = DEF_HEIGHT;

	_data->mlx_ptr = mlx_init(_data->width, _data->height, "Game of life", true);
	if (!_data->mlx_ptr) return release(_data, 1);

	_data->mlx_img = mlx_new_image(_data->mlx_ptr, _data->width, _data->height);
	if (!_data->mlx_img) return release(_data, 1);

	_data->PPC = DEF_PPC;
	_data->FPG = DEF_FPG;
	_data->_world->center_x = (_data->width / 2) * _data->PPC;
	_data->_world->center_y = (_data->height / 2) * _data->PPC;
	_data->_world->rows = _data->height / _data->PPC;
	_data->_world->columns = _data->width / _data->PPC;
	draw_bg(_data, BG_COLOR << 8 | 0xFF);
	
	mlx_image_to_window(_data->mlx_ptr, _data->mlx_img, 0, 0);
	init_world(_data, c == 2 ? v : NULL);
	mlx_close_hook(_data->mlx_ptr, close_handle, _data);
	mlx_key_hook(_data->mlx_ptr, key_handle, _data);
	mlx_resize_hook(_data->mlx_ptr, resize_handle, _data);
	mlx_scroll_hook(_data->mlx_ptr, scroll_handle, _data);
	mlx_cursor_hook(_data->mlx_ptr, cursor_handle, _data);
	mlx_mouse_hook(_data->mlx_ptr, mouse_handle, _data);
	mlx_loop_hook(_data->mlx_ptr, loop_hook, _data);
	mlx_loop(_data->mlx_ptr);
}
