#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(double l_x, double r_x, double l_y, double r_y, double _dx, double _dy)
{
	l_x_bound = l_x;
	r_x_bound = r_x;
	l_y_bound = l_y;
	r_y_bound = r_y;


	dx = _dx;
	dy = _dy;

	steps_x = 0;
	steps_y = 0;

	for (double i = l_x_bound; i < r_x_bound; i += dx)
	{
		grid_x.push_back(i);
		steps_x++;
	}

	for (double i = l_y_bound; i < r_y_bound; i += dy)
	{
		grid_y.push_back(i);
		steps_y++;
	}

	grid_x.push_back(r_x_bound);
	grid_y.push_back(r_y_bound);
	steps_x++;
	steps_y++;
}


Grid::~Grid()
{
}
