#pragma once
#include "Grid.h"
#include <string>

class Task
{
public:
	Task(const double _time_max, const double _dx, const double _dy, const double _K);
	~Task();

	void set_init_conditions();
	void compute_on_host(const double _K);
	void compute_on_device();

	void record_values(std::string file_name);

private:
	Grid grid;

	int size_x, size_y;
	int SIZE;

	double dx, dy;

	double **E_x = nullptr;
	double **E_x1 = nullptr;
	
	double **E_y = nullptr;
	double **E_y1 = nullptr;
	
	double **H_z = nullptr;
	double **H_z1 = nullptr;

	double **tmp = nullptr;

	double time_max;
	double dt;

	vector<double> coord_x;
	vector<double> coord_y;

};

