#include "convex_ohq.h"

// for key=lambda p: (-p[1], p[0])
bool o_hull_compare_function_xy_hull1(Point2D a, Point2D b)
{
	if (a.x == b.x)
		return a.y > b.y;
	return a.x < b.x;
}

// for key=lambda p: (p[0], -p[1])
bool o_hull_compare_function_yx_hull1(Point2D a, Point2D b)
{
	if (a.y == b.y)
		return a.x < b.x;
	return a.y > b.y;
}



// for key=lambda p: (p[0], p[1])
bool o_hull_compare_function_xy_hull2(Point2D a, Point2D b)
{
	if (a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

// for key=lambda p: (p[1], p[0])
bool o_hull_compare_function_yx_hull2(Point2D a, Point2D b)
{
	if (a.y == b.y)
		return a.x < b.x;
	return a.y < b.y;
}



// for key=lambda p: (-p[0], p[1])
bool o_hull_compare_function_xy_hull3(Point2D a, Point2D b)
{
	if (a.x == b.x)
		return a.y < b.y;
	return a.x > b.x;
}

// for key=lambda p: (p[1], -p[0])
bool o_hull_compare_function_yx_hull3(Point2D a, Point2D b)
{
	if (a.y == b.y)
		return a.x > b.x;
	return a.y < b.y;
}



// for key=lambda p: (-p[0], -p[1])
bool o_hull_compare_function_xy_hull4(Point2D a, Point2D b)
{
	if (a.x == b.x)
		return a.y > b.y;
	return a.x > b.x;
}

// for key = lambda p : (-p[1], -p[0])
bool o_hull_compare_function_yx_hull4(Point2D a, Point2D b)
{
	if (a.y == b.y)
		return a.x > b.x;
	return a.y > b.y;
}





// for key = lambda x : x[0]
bool o_hull_compare_x(Point2D a, Point2D b)
{
	return a.x > b.x;
}

// for key = lambda x : x[0]
bool o_hull_compare_y(Point2D a, Point2D b)
{
	return a.y > b.y;
}

/*
* Parameter:
*	- set: set of points that o_hull came from
*	- q, qq: 2 points that indent the 
			leftmost-rightmost pair or 
			highest-lowest pair
*/
DataPoints& general_find_o_hull(DataPoints& set, Point2D q, Point2D qq, bool (*compare_1)(Point2D, Point2D), bool (*compare_2)(Point2D, Point2D))
{
	if (set.data.size() == 0)
		return *(new DataPoints());

	DataPoints* hull_set = new DataPoints();
	DataPoints sorted_set_xy(set);
	DataPoints sorted_set_yx(set);

#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			sort(sorted_set_xy.data.begin(), sorted_set_xy.data.end(), compare_1);
#pragma omp section
			sort(sorted_set_yx.data.begin(), sorted_set_yx.data.end(), compare_2);
		}
	}

	Point2D new_q(sorted_set_yx.data[0]);
	Point2D new_qq(sorted_set_xy.data[0]);

	DataPoints new_set;
#pragma omp parallel
	{
		DataPoints private_list;
#pragma omp for nowait
		for (int i = 0; i < int(set.data.size()); i++)
		{
			if (set.data[i].is_inside(new_q, new_qq))
				private_list.push(set.data[i]);
		}

#pragma omp critical
		new_set + private_list;
	}

	hull_set->data.push_back(new_q);
	(*hull_set) + general_find_o_hull(new_set, new_q, new_qq, compare_1, compare_2);
	hull_set->data.push_back(new_qq);
	return *hull_set;
}


void find_o_hull1(DataPoints& result, DataPoints& set1, Point2D q1, Point2D qq1)
{
	result = *(new DataPoints(q1)) + general_find_o_hull(set1, q1, qq1, o_hull_compare_function_xy_hull1, o_hull_compare_function_yx_hull1) + *(new DataPoints(qq1));
}

void find_o_hull2(DataPoints& result, DataPoints& set2, Point2D q2, Point2D qq2)
{
	result = *(new DataPoints(q2)) + general_find_o_hull(set2, q2, qq2, o_hull_compare_function_xy_hull2, o_hull_compare_function_yx_hull2) + *(new DataPoints(qq2));
}

void find_o_hull3(DataPoints& result, DataPoints& set3, Point2D q3, Point2D qq3)
{
	result = *(new DataPoints(q3)) + general_find_o_hull(set3, q3, qq3, o_hull_compare_function_xy_hull3, o_hull_compare_function_yx_hull3) + *(new DataPoints(qq3));
}

void find_o_hull4(DataPoints& result, DataPoints& set4, Point2D q4, Point2D qq4)
{
	result = *(new DataPoints(q4)) + general_find_o_hull(set4, q4, qq4, o_hull_compare_function_xy_hull4, o_hull_compare_function_yx_hull4) + *(new DataPoints(qq4));
}


void filter(DataPoints& points, DataPoints& original_set, Point2D q, Point2D qq)
{
#pragma omp parallel
	{
		DataPoints private_points;
#pragma omp for nowait
		for (int i = 0; i<int(original_set.data.size()); i++)
		{
			if (original_set.data[i].is_inside(q, qq))
				private_points.push(original_set.data[i]);
		}

#pragma omp critical
		points + private_points;
	}
}

DataPoints& find_orthogonal_convex_hull(DataPoints& points)
{
	vector<Point2D> top_points;
	vector<Point2D> bottom_points;
	vector<Point2D> left_points;
	vector<Point2D> right_points;

#pragma omp parallel num_threads(1)
	{
		vector<Point2D> private_top_points;
		vector<Point2D> private_bottom_points;
		vector<Point2D> private_left_points;
		vector<Point2D> private_right_points;
#pragma omp for nowait
		for (int i = 0; i < int(points.data.size()); i++)
		{
			if (points.data[i].x == points.maxX)
				private_right_points.push_back(points.data[i]);

			if (points.data[i].x == points.minX)
				private_left_points.push_back(points.data[i]);

			if (points.data[i].y == points.maxY)
				private_top_points.push_back(points.data[i]);

			if (points.data[i].y == points.minY)
				private_bottom_points.push_back(points.data[i]);
		}

#pragma omp critical
		{
			top_points.insert(top_points.end(), private_top_points.begin(), private_top_points.end());
			bottom_points.insert(bottom_points.end(), private_bottom_points.begin(), private_bottom_points.end());
			left_points.insert(left_points.end(), private_left_points.begin(), private_left_points.end());
			right_points.insert(right_points.end(), private_right_points.begin(), private_right_points.end());
		}
	}

	vector<Point2D> sorted_top(top_points);
	vector<Point2D> sorted_bottom(bottom_points);
	vector<Point2D> sorted_left(left_points);
	vector<Point2D> sorted_right(right_points);

#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			sort(sorted_top.begin(), sorted_top.end(), o_hull_compare_y);
#pragma omp section
			sort(sorted_bottom.begin(), sorted_bottom.end(), o_hull_compare_y);
#pragma omp section
			sort(sorted_left.begin(), sorted_left.end(), o_hull_compare_x);
#pragma omp section
			sort(sorted_right.begin(), sorted_right.end(), o_hull_compare_x);
		}
	}

	Point2D q1 = sorted_top[0];
	Point2D qq4 = sorted_top[sorted_top.size() - 1];

	Point2D q2 = sorted_left[sorted_left.size() - 1];
	Point2D qq1 = sorted_left[0];

	Point2D q3 = sorted_bottom[sorted_bottom.size() - 1];
	Point2D qq2 = sorted_bottom[0];

	Point2D q4 = sorted_right[0];
	Point2D qq3 = sorted_right[sorted_right.size() - 1];

	DataPoints set1;
	DataPoints set2;
	DataPoints set3;
	DataPoints set4;

#pragma omp parallel
#pragma omp sections
	{
#pragma omp section
		filter(set1, points, q1, qq1);
#pragma omp section
		filter(set2, points, q2, qq2);
#pragma omp section
		filter(set3, points, q3, qq3);
#pragma omp section
		filter(set4, points, q4, qq4);
	}

	DataPoints part1;
	DataPoints part2;
	DataPoints part3;
	DataPoints part4;

#pragma omp parallel
#pragma omp sections
	{
#pragma omp section
		find_o_hull1(part1, set1, q1, qq1);
#pragma omp section
		find_o_hull2(part2, set2, q2, qq2);
#pragma omp section
		find_o_hull3(part3, set3, q3, qq3);
#pragma omp section
		find_o_hull4(part4, set4, q4, qq4);
	}

	cout << part1.data.size() << " " << part2.data.size() << " " << part3.data.size() << " " << part4.data.size() << endl;

	DataPoints* arranged_points = new DataPoints(part1 + part2 + part3 + part4);
	return *arranged_points;
}

extern "C"
{
	void __declspec(dllexport) findOrthogonalConvexHull(string input_file_name, string output_file_name)
	{
		DataPoints data(input_file_name);
		DataPoints orthogonal_hull = find_orthogonal_convex_hull(data);
		to_file(output_file_name, orthogonal_hull);
	}

	/*void __declspec(dllexport) findOrthogonalConvexHull(char* input_file_name, char* output_file_name)
	{
		string input_file(input_file_name);
		string output_file(output_file_name);
		DataPoints data(input_file);
		DataPoints orthogonal_hull = find_orthogonal_convex_hull(data);
		to_file(output_file, orthogonal_hull);
	}
	*/
}