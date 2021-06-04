#include "data.h"
#include "utils.h"

using namespace std;


void Point2D::from_string(string raw_str)
{
	int comma_place = raw_str.find(',', 0);
	raw_str.replace(raw_str.begin() + comma_place, raw_str.begin() + comma_place + 1, 1, ' ');
	stringstream stream(raw_str);
	double a, b;
	stream >> a >> b;

	this->x = a;
	this->y = b;
}

void Point2D::set_point(double* point)
{
	this->x = point[0];
	this->y = point[1];
}

void Point2D::set_point(const Point2D& point)
{
	this->x = point.x;
	this->y = point.y;
}

double* Point2D::to_pointer()
{
	return new double[] {this->x, this->y};
}

bool Point2D::operator==(const Point2D& another)
{
	return this->x == another.x && this->y == another.y;
}

bool Point2D::is_inside(const Point2D& a, const Point2D& b)
{
	if ((*this == a) || (*this == b))
		return false;
	else
		return	in_range<double>(this->x, a.x, b.x) &&
				in_range<double>(this->y, a.y, b.y);

}




void DataPoints::load(string file_name)
{
	ifstream file;
	file.open(file_name);

	int lines_count = get_line_count(file_name);
	DataPoints& storage = *this;

#pragma omp parallel
	{
		DataPoints private_list;
#pragma omp for schedule(dynamic) nowait
		for (int i = 0; i <= lines_count; i++)
		{
			string h;
			getline(file, h, '\n');
			if (h == "")continue;

			Point2D* point = new Point2D();
			point->from_string(h);

			private_list.push((*point));
		}
#pragma omp critical
		(*this) + private_list;
	}

	file.close();
}

Point2D DataPoints::get_point(int index)
{
	return this->data[index];
}

void DataPoints::push(const Point2D& point)
{
	this->__update_on_push(point);
	this->data.push_back(point);
}

DataPoints& DataPoints::operator+(const DataPoints& point_list)
{
	this->__update_on_merge(point_list);
	this->data.insert(this->data.end(), point_list.data.begin(), point_list.data.end());
	return *this;
}
