#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "data.h"

using namespace std;

template<class Type>
bool in_range(Type a, Type b, Type c)
{
	return	(a >= min<Type>(b, c)) &&
		(a <= max<Type>(b, c));
}

int get_line_count(string file_name);
void to_file(string file_name, DataPoints& data);

#endif