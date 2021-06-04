#include "utils.h"

int get_line_count(string file_name)
{
	ifstream file;
	file.open(file_name);
	int n = count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
	file.close();
	return n;
}

void to_file(string file_name, DataPoints& data)
{
	ofstream file(file_name);
	for (int i = 0; i < data.data.size(); i++)
		file << data.data[i].x << " ," << data.data[i].y << endl;
	file.close();
}