#include "gol.h"

void	insert_seed(data *_data, char **v) {
	_data->input = fopen(v[1], "r");
	if (!_data->input)
		return;
	int		read;
	int		x, y;
	int		w = 0, h = 0;
	size_t		size = 1024;
	char		*buffer = malloc(size);

	if (!buffer) {
		fclose(_data->input);
		_data->input = NULL;
		return;
	}

	while ((read = getline(&buffer, &size, _data->input)) > 0) {
		if (buffer[0] == '#')	continue;
		else if (buffer[0] == 'x') {
			int i = 1;
			while (i < read && !isdigit(buffer[i]))
				i++;
			while (i < read && isdigit(buffer[i]) && w < _data->_world->columns)
				w = w * 10 + (buffer[i++] - '0');
			while (i < read && buffer[i] != 'y')
				i++;
			if (buffer[i] == 'y') {
				while (i < read && !isdigit(buffer[i])) i++;
				while (i < read && isdigit(buffer[i]) && h < _data->_world->rows)
					h = h * 10 + (buffer[i++] - '0');
			}
			if (!w || !h || w > _data->_world->columns || h > _data->_world->rows) {
				fclose(_data->input);
				_data->input = NULL;
				free(buffer);
				return;
			}
			x = (_data->_world->columns - w) / 2;
			y = (_data->_world->rows - h) / 2;
		}
		else if (w && h) {
			int	accu;
			for (int i = 0; i < read; i++) {
				accu = 1;
				if (isdigit(buffer[i])) {
					accu = 0;
					while (i < read && isdigit(buffer[i]))
						accu = accu * 10 + (buffer[i++] - 48);
				}
				if (buffer[i] == '$') {
					while (accu--) {
						x = (_data->_world->columns - w) / 2;
						y++;
						if (y >= _data->_world->rows) {
							fclose(_data->input);
							_data->input = NULL;
							free(buffer);
							return;
						}
					}
				}
				else if (buffer[i] == '!') {
					fclose(_data->input);
					_data->input = NULL;
					free(buffer);
					return;
				}
				else if (buffer[i] == 'b') { 
					while (accu--) _data->_world->population[y][x++] = FALSE;
					if (x >= _data->_world->columns) break;
				}
				else if (buffer[i] == 'o') {
					while (accu--) _data->_world->population[y][x++] = TRUE;
					if (x >= _data->_world->columns) break;
				}
			}
		}
	}
	
	fclose(_data->input);
	_data->input = NULL;
	free(buffer);
}
