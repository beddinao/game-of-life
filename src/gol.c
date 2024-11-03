#include "gol.h"

void	build_population(data *_data, bool seed) {
	_data->_world->population = malloc( (_data->_world->rows + 1) * sizeof(bool*) );
	if (!_data->_world->population)
		exit( release(_data, 1) );
	for (int y = 0; y < _data->_world->rows; y++) {
		_data->_world->population[y] = malloc( _data->_world->columns * sizeof(bool) );
		if (!_data->_world->population[y]) exit( release(_data, 1) );
		//
		if (!seed)
			for (int x = 0; x < _data->_world->columns; x++)
				_data->_world->population[y][x] = rand_num(FALSE, TRUE);
		else	memset(_data->_world->population[y], FALSE, sizeof(bool) * _data->_world->columns);
	}
	_data->_world->population[ _data->_world->rows ] = NULL;
}

void	updata_population(data *_data) {
	//	game-of-life rules
	int	live_neighbors, c_row, c_column;
	int	temp_population[_data->_world->rows][_data->_world->columns];
	memset(temp_population, FALSE, _data->_world->columns * _data->_world->rows);

	_data->_world->generation += 1;
	_data->_world->current_population = 0;
	for (int row = 0; row < _data->_world->rows; row++)
		for (int column = 0; column < _data->_world->columns; column++) {
			live_neighbors = 0;

			c_row = row;
			c_column = column + 1;
			if (c_column >= _data->_world->columns)
				c_column = 0;
			live_neighbors += _data->_world->population[c_row][c_column];

			c_row = row + 1;
			if (c_row >= _data->_world->rows)
				c_row = 0;
			live_neighbors += _data->_world->population[c_row][c_column];

			c_row = row - 1;
			if (c_row < 0)
				c_row = _data->_world->rows - 1;
			live_neighbors += _data->_world->population[c_row][c_column];

			c_row = row;
			c_column = column - 1;
			if (c_column < 0)
				c_column = _data->_world->columns - 1;
			live_neighbors += _data->_world->population[row][c_column];

			c_row = row + 1;
			if (c_row >= _data->_world->rows)
				c_row = 0;
			live_neighbors += _data->_world->population[c_row][c_column];

			c_row = row - 1;
			if (c_row < 0)
				c_row = _data->_world->rows - 1;
			live_neighbors += _data->_world->population[c_row][c_column];

			c_column = column;
			c_row = row + 1;
			if (c_row >= _data->_world->rows)
				c_row = 0;
			live_neighbors += _data->_world->population[c_row][c_column];

			c_row = row - 1;
			if (c_row < 0)
				c_row = _data->_world->rows - 1;
			live_neighbors += _data->_world->population[c_row][c_column];
			//
			if (_data->_world->population[row][column]) {
				if (live_neighbors < 2) // underpopulation
					temp_population[row][column] = FALSE;
				else if (live_neighbors > 3) // overpopulation
					temp_population[row][column] = FALSE;
				else	temp_population[row][column] = TRUE;
			}
			else if (!_data->_world->population[row][column] && live_neighbors == 3)
				temp_population[row][column] = TRUE;
			else	temp_population[row][column] = _data->_world->population[row][column];
			//
			_data->_world->current_population += temp_population[row][column];
		}

	for (int row = 0; row < _data->_world->rows; row++)
		for (int column = 0; column < _data->_world->columns; column++)
			_data->_world->population[row][column] = temp_population[row][column];
}

