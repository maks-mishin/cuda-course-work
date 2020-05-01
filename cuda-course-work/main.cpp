#include "Grid.h"
#include "Task.h"
#include <time.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "calculation.h"


int main()
{
	const double time_max = 2.0;
	const double K = 0.5;

	Task task(time_max, 0.01, 0.01, K);
	task.compute_on_host(K);
	task.record_values("H_z.txt");
}