/*
	Simple realization of FDTD algorithm for solving TE(z) waves.
	TE - magnetic wave. E(z) = 0, H(z) != 0.

*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <math.h>
#include <iomanip>
#include "Task.h"
#include "calculation.h"

void print(double** arr, int size_x, int size_y)
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			cout << arr[i][j] << " ";

			//cout << fixed << setprecision(8) << arr[i][j] << " ";
			if (j == size_y - 1)
				cout << endl;
		}
	}
}

using namespace std;
Task::Task(const double _time_max, const double _dx, const double _dy, const double _K)
{

	time_max = _time_max;
	Grid grid(0, 1, 0, 1, _dx, _dy);

	coord_x = grid.get_grid_x();
	coord_y = grid.get_grid_y();

	size_x = grid.get_steps_x();
	size_y = grid.get_steps_y();

	SIZE = size_x*size_y;

	dx = grid.get_dx();
	dy = grid.get_dy();

	set_init_conditions();
}


Task::~Task()
{
	for (int i = 0; i < size_x; i++) {
		delete[]E_x[i];
		delete[]E_y[i];
		delete[]H_z[i];
	}
	delete[]E_x;
	delete[]E_y;
	delete[]H_z;
}

void Task::set_init_conditions()
{
	double pi = 4 * atan(1.0);
	E_x = new double*[size_x];
	E_y = new double*[size_x+1];
	H_z = new double*[size_x];

	for (int i = 0; i < size_x; i++)
	{
		E_x[i] = new double[size_y+1];
		E_y[i] = new double[size_y];
		H_z[i] = new double[size_y];
	}

	// Add fake values to three-dimensional mesh
	coord_x.resize(coord_x.size() + 1);
	coord_y.resize(coord_y.size() + 1);


	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			E_x[i][j] = sin(pi*(coord_x[i+1] + coord_x[i])/2)*cos((pi/3)*coord_y[j]);
		}
	}
	
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			E_y[i][j] = -sin(pi*(coord_y[j + 1] + coord_y[j]) / 2)*cos((pi/6)*coord_x[i]);
		}
	}

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			H_z[i][j] = sin(pi*(coord_x[i] + coord_x[i+1]) / 2)*cos((pi/4)*(coord_y[j] + coord_y[j+1]) / 2);
		}
	}
}

void Task::compute_on_host(const double _K)
{
	double pi = 4 * atan(1.0);


	//c = 1 - speed of light in structure
	dt = dx*dy;//1/(sqrt(1/dx*dx + 1/dy*dy));
	//cout << "Step on time: " << dt << endl;
	cout << "Source H_z" << endl;
	//print(H_z, size_x, size_y);

	double current_time = 0.0;
	do
	{
		//std::cout << "Time: " << current_time << std::endl;
		if (time_max - current_time < dt)
			dt = time_max - current_time;

		// update H-field
		for (int i = 1; i < size_x - 1; i++)
		{
			for (int j = 1; j < size_y - 1; j++)
			{
				H_z[i][j] = H_z[i][j] + dt*((E_x[i][j + 1] - E_x[i][j]) / dy - (E_y[i + 1][j] - E_y[i][j]) / dx);
			}
		}

		// update E-field
		for (int i = 1; i < size_x - 1; i++)
		{
			for (int j = 1; j < size_y - 1; j++)
			{
				E_x[i][j] = E_x[i][j] + dt*(H_z[i][j] - H_z[i][j - 1]) / dy;
				E_y[i][j] = E_y[i][j] - dt*(H_z[i][j] - H_z[i-1][j]) / dy;
			}
		}

		current_time += dt;
	} while (current_time  < time_max);

	cout << endl << "Result H_z" << endl;
	//print(H_z, size_x, size_y);
}

void Task::record_values(std::string file_name)
{
	std::ofstream out;

	out.open(file_name);

	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
		{
			out << E_x[i][j] << " ";
			if (j == size_y - 1)
			{
				out << std::endl;
			}
		}

	out.close();
}
