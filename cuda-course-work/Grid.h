#pragma once
#include <vector>

using namespace std;

class Grid
{
public:
	Grid();
	Grid(double l_x, double r_x, double l_y, double r_y, double _dx, double _dy);
	~Grid();

	std::vector<double> get_grid_x() const { return grid_x; }
	std::vector<double> get_grid_y() const { return grid_y; }

	int get_steps_x() const { return steps_x; }
	int get_steps_y() const { return steps_y; }

	double get_dx() const { return dx; }
	double get_dy() const { return dy; }

private:
	// Tree-dimensional mesh
	std::vector<double> grid_x;
	std::vector<double> grid_y;

	//Amount of steps on X and Y
	int steps_x, steps_y;

	// Steps on X and Y
	double dx, dy;

	//Boundaries of area
	double l_x_bound, r_x_bound, l_y_bound, r_y_bound;
};

