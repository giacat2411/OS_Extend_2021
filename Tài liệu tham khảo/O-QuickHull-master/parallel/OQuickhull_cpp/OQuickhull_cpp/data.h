#ifndef __DATA_H_LIB
#define __DATA_H_LIB

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <omp.h>
#include <vector>

using namespace std;

class Point
{
protected:
	Point() {};

public:
	virtual void set_point(double* point)		= 0;
	virtual void from_string(string str)		= 0;
	virtual double* to_pointer()				= 0;
};

class Point2D:public Point
{
public:
	double x, y;

	Point2D()
	{
		this->x = 0;
		this->y = 0;
	}

	Point2D(double* point)
	{
		this->x = point[0];
		this->y = point[1];
	}

	Point2D(const Point2D &point)
	{
		this->x = point.x;
		this->y = point.y;
	}

	Point2D(double a, double b)
	{
		this->x = a;
		this->y = b;
	}

	void set_point(const Point2D& new_point);
	bool is_inside(const Point2D&, const Point2D&);
	string to_string()
	{
		stringstream stream;
		stream << this->x << "_" << this->y;
		string h;
		stream >> h;
		return h;
	}

	void set_point(double* point)	override;
	void from_string(string str)	override;
	double* to_pointer()			override;

	bool operator == (const Point2D&);
};

class DataPoints
{
public: // Variable and Constructor declarations
	vector<Point2D> data;

	double maxX;
	double maxY;
	double minX;
	double minY;

	Point2D* q1;
	Point2D* qq1;

	Point2D* q2;
	Point2D* qq2;

	Point2D* q3;
	Point2D* qq3;

	Point2D* q4;
	Point2D* qq4;

	DataPoints()
	{
		this->__base_init();
	}

	DataPoints(const string h)
	{
		this->__base_init();
		this->load(h);
	}

	DataPoints(const Point2D& point)
	{
		this->__update_on_push(point);
		this->push(point);
	}

	DataPoints(const DataPoints& point_list)
	{
		*this = point_list;
	}

private:
	void __base_init()
	{
		this->maxX = this->maxY = -INT32_MAX;
		this->minX = this->minY = INT32_MAX;
	}

	void __update_on_push(const Point2D& point) // when add point to list
	{
		if (point.x > this->maxX)
			this->maxX = point.x;
		if (point.x < this->minX)
			this->minX = point.x;

		if (point.y > this->maxY)
			this->maxY = point.y;
		if (point.y < this->minY)
			this->minY = point.y;
	}

	void __update_on_merge(const DataPoints& point_list) // when merge from another list
	{
		if (this->maxX < point_list.maxX)
			this->maxX = point_list.maxX;
		if (this->minX > point_list.minX)
			this->minX = point_list.minX;

		if (this->maxY < point_list.maxY)
			this->maxY = point_list.maxY;
		if (this->minY > point_list.minY)
			this->minY = point_list.minY;
	}
public:
	void load(string file_name);
	Point2D get_point(int index);
	void push(const Point2D&);

	DataPoints& operator = (const DataPoints& point_list)
	{
		this->data = point_list.data;
		this->__update_on_merge(point_list);
		return *this;
	}

	DataPoints& operator + (const DataPoints&);
};


#endif // !__DATA_H_LIB