#ifndef __CONVEX_OHQ_H
#define __CONVEX_OHQ_H

#include <iostream>
#include <algorithm>	//std::sort
#include <omp.h>		//parallel library
#include <vector>

#include "data.h"
#include "utils.h"

using namespace std;

void find_o_hull1(DataPoints&, DataPoints&, Point2D, Point2D);
void find_o_hull2(DataPoints&, DataPoints&, Point2D, Point2D);
void find_o_hull3(DataPoints&, DataPoints&, Point2D, Point2D);
void find_o_hull4(DataPoints&, DataPoints&, Point2D, Point2D);

DataPoints& find_orthogonal_convex_hull(DataPoints&);

extern "C"
{
	void findOrthogonalConvexHull(char* input_file_name, char* output_file_name);
}

#endif