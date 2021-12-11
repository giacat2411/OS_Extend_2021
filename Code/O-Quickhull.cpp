#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

// Class bieu diem diem phang
class Point
{
    float x, y;

public:
    Point()  { x = 0; y = 0; }

    Point(float x, float y) { this->x = x; this->y = y; }

    float get_x() { return x; }

    float get_y() { return y; }

    void set_x(float x) { this->x = x; }

    void set_y(float y) { this->y = y; }

    // Diem co nam trong duong truc giao truc tiep qua a b hay khong ?
    // Nam trong -> a.x < x < b.x va a.y < y < b.y
    bool is_inside(Point a, Point b) {
        float min_x = min(a.x, b.x);
        float max_x = max(a.x, b.x);
        float min_y = min(a.y, b.y);
        float max_y = max(a.y, b.y);

        if ((min(a.x, b.x) < this->x) && (max(a.x, b.x) > this->x) && (min(a.y, b.y) < this->y) && (max(a.y, b.y) > this->y))
            return true;
        return false;
    }

    void print_Point() {
        cout << "(" << this->x << "," << this->y << ") ";
    }

    bool operator==(Point other) {
        return ((abs(x - other.x) < 0.01) && (abs(y - other.y)) < 0.01);
    }

    bool operator!=(Point other) {
        return ((x != other.x) || (y != other.y));
    }
};

// Chuyen mot xau thanh cap diem x y
// Vd: Input = "3.4, 2.7"
// Output: (Point)(3.4;2.7)
Point to_Point(string line)
{
    int i = 0;
    string x, y;
    float to_x, to_y;

    x = y = "";

    while (line[i] != ',')
    {
        x += line[i];
        i++;
    }

    i++;

    for (int j = i; j < line.length(); j++)
        y += line[j];

    while (x.find(' ') != -1)
        x.erase(x.begin() + x.find(' '));
    while (y.find(' ') != -1)
        y.erase(y.begin() + y.find(' '));

    to_x = stof(x);
    to_y = stof(y);

    Point convert(to_x, to_y);

    return convert;
}

float square_distance(Point p1, Point p2)
{
    return float(pow(p1.get_x() - p2.get_x(), 2) + pow(p1.get_y() - p2.get_y(), 2));
}

Point max_distance(vector<Point> points, Point root)
{
    Point max = points[0];
    float _max_distance = square_distance(points[0], root);

    for (int i = 1; i < points.size(); i++)
    {
        float distance = square_distance(points[i], root);
        if (distance > _max_distance)
        {
            _max_distance = distance;
            max = points[i];
        }
    }
    return max;
}

// Tim 8 diem cuc
// Array[0]: highest-leftmost; Array[1]: leftmost-highest
// Array[2]: lowest-leftmost; Array[3]: leftmost-lowest
// Array[4]: lowest-rightmost; Array[5]: rightmost-lowest
// Array[6]: highest-rightmost; Array[7]: rightmost-highest
vector<Point> _8_extreme_point(vector<Point> points)
{
    vector<Point> _8_extreme;
    for (int i = 0; i < 8; i++)
        _8_extreme.push_back(points[0]);

    float xmin = points[0].get_x();
    float xmax = points[0].get_x();
    float ymin = points[0].get_y();
    float ymax = points[0].get_y();

    for (int i = 1; i < points.size(); i++)
    {
        if (points[i].get_x() < xmin)
        {
            xmin = points[i].get_x();
            _8_extreme[0] = points[i];
            _8_extreme[2] = points[i];
        }
        else if (points[i].get_x() > xmax)
        {
            xmax = points[i].get_x();
            _8_extreme[4] = points[i];
            _8_extreme[6] = points[i];
        }
        else if (points[i].get_x() == xmin)
        {
            if (points[i].get_y() > _8_extreme[0].get_y())
                _8_extreme[0] = points[i];
            if (points[i].get_y() < _8_extreme[2].get_y())
                _8_extreme[2] = points[i];
        }
        else if (points[i].get_x() == xmax)
        {
            if (points[i].get_y() > _8_extreme[6].get_y())
                _8_extreme[6] = points[i];
            if (points[i].get_y() < _8_extreme[4].get_y())
                _8_extreme[4] = points[i];
        }

        if (points[i].get_y() > ymax)
        {
            ymax = points[i].get_y();
            _8_extreme[1] = points[i];
            _8_extreme[7] = points[i];
        }
        else if (points[i].get_y() < ymin)
        {
            ymin = points[i].get_y();
            _8_extreme[3] = points[i];
            _8_extreme[5] = points[i];
        }
        else if (points[i].get_y() == ymax)
        {
            if (points[i].get_x() > _8_extreme[7].get_x())
                _8_extreme[7] = points[i];
            if (points[i].get_x() < _8_extreme[1].get_x())
                _8_extreme[1] = points[i];
        }
        else if (points[i].get_y() == ymin)
        {
            if (points[i].get_x() > _8_extreme[5].get_x())
                _8_extreme[5] = points[i];
            if (points[i].get_x() < _8_extreme[3].get_x())
                _8_extreme[3] = points[i];
        }
    }

    return _8_extreme;
}

// Noi hai vector lai voi nhau
// Input: a b
// Ouput: c = a + b
vector<Point> plus_vector(vector<Point> set1, vector<Point> set2)
{
    vector<Point> result;
    for (int i = 0; i < set1.size(); i++)
        result.push_back(set1[i]);

    for (int i = 0; i < set2.size(); i++)
        result.push_back(set2[i]);

    return result;
}

// Kiem tra xem tap diem co hai diem trung nhau hay khong
// Neu co, xoa diem trung
void check(vector<Point> &points)
{
    for (int i = 0; i < points.size(); i++)
        for (int j = i + 1; j < points.size(); j++)
            if (points[i] == points[j])
            {
                points.erase(points.begin() + j);
                j--;
            }
}

// q1, qq1 phai dung dinh dang nhu trong li thuyet
// q1.x > qq1.x; q1.y > qq1.y
// q2.x < qq2.x; q2.y > qq2.y
// q3.x < qq3.x; q3.y < qq3.y
// q4.x > qq4.x; q4.y < qq4.y

// Tim bao loi tren mien 1
// Trong do q1, qq1: diem dac biet cua mien
//          convex_hull1: tap cac diem thuoc bao loi
//          set1: tap cac diem thuoc mien
// Ket qua cap nhat truc tiep vao convex_hull1
void find_Convex_Hull1(Point q1, Point qq1, vector<Point> &convex_hull1, vector<Point> set1);

// Tuong tu mien 1
void find_Convex_Hull2(Point q2, Point qq2, vector<Point> &convex_hull2, vector<Point> set2);
void find_Convex_Hull3(Point q3, Point qq3, vector<Point> &convex_hull3, vector<Point> set3);
void find_Convex_Hull4(Point q4, Point qq4, vector<Point> &convex_hull4, vector<Point> set4);

// Tim bao loi cua mot tap diem
// Input: points: tap diem
// Output: Vector chua cac diem thuoc bao loi
vector<Point> find_Convex_Hull(vector<Point> points)
{
    vector<Point> hull;
    hull.clear();

    // Tim 8 diem dac biet cua tap diem
    // Array[0]: highest-leftmost; Array[1]: leftmost-highest
    // Array[2]: lowest-leftmost; Array[3]: leftmost-lowest
    // Array[4]: lowest-rightmost; Array[5]: rightmost-lowest
    // Array[6]: highest-rightmost; Array[7]: rightmost-highest

    vector<Point> _8_extreme = _8_extreme_point(points);

    Point highest_leftmost = _8_extreme[0]; // Convex_hull 1
    Point leftmost_highest = _8_extreme[1];

    Point lowest_leftmost = _8_extreme[2]; // Convex_hull 2
    Point leftmost_lowest = _8_extreme[3];

    Point lowest_rightmost = _8_extreme[4]; // Convex_hull 3
    Point rightmost_lowest = _8_extreme[5];

    Point highest_rightmost = _8_extreme[6]; // Convex_hull 4
    Point rightmost_highest = _8_extreme[7];

    vector<Point> convex_hull1, convex_hull2, convex_hull3, convex_hull4; // Tap cac diem cuc bien 4 mien
    vector<Point> set1, set2, set3, set4;                                 // Tap diem cua 4 mien do

    convex_hull1.clear();
    convex_hull2.clear();
    convex_hull3.clear();
    convex_hull4.clear();

    set1.clear();
    set2.clear();
    set3.clear();
    set4.clear();

    // TIM CAC DIEM CUA MOI MIEN
    if (highest_leftmost == leftmost_highest)
        convex_hull1.push_back(highest_leftmost);
    else
    {
        convex_hull1.push_back(highest_leftmost);
        convex_hull1.push_back(leftmost_highest);

        for (int i = 0; i < points.size(); i++)
            if (points[i].is_inside(highest_leftmost, leftmost_highest))
                set1.push_back(points[i]);
    }

    if (lowest_leftmost == leftmost_lowest)
        convex_hull2.push_back(lowest_leftmost);
    else
    {
        convex_hull2.push_back(lowest_leftmost);
        convex_hull2.push_back(leftmost_lowest);

        for (int i = 0; i < points.size(); i++)
            if (points[i].is_inside(lowest_leftmost, leftmost_lowest))
                set2.push_back(points[i]);
    }

    if (lowest_rightmost == rightmost_lowest)
        convex_hull3.push_back(lowest_rightmost);
    else
    {
        convex_hull3.push_back(lowest_rightmost);
        convex_hull3.push_back(rightmost_lowest);

        for (int i = 0; i < points.size(); i++)
            if (points[i].is_inside(lowest_rightmost, rightmost_lowest))
                set3.push_back(points[i]);
    }

    if (highest_rightmost == rightmost_highest)
        convex_hull4.push_back(highest_rightmost);
    else
    {
        convex_hull4.push_back(highest_rightmost);
        convex_hull4.push_back(rightmost_highest);

        for (int i = 0; i < points.size(); i++)
            if (points[i].is_inside(highest_rightmost, rightmost_highest))
                set4.push_back(points[i]);
    }

    // TIM CAC DIEM THUOC BAO LOI CUA 4 MIEN
    find_Convex_Hull1(leftmost_highest, highest_leftmost, convex_hull1, set1);
    find_Convex_Hull2(lowest_leftmost, leftmost_lowest, convex_hull2, set2);
    find_Convex_Hull3(rightmost_lowest, lowest_rightmost, convex_hull3, set3);
    find_Convex_Hull4(highest_rightmost, rightmost_highest, convex_hull4, set4);

    hull = plus_vector(plus_vector(plus_vector(convex_hull1, convex_hull2), convex_hull3), convex_hull4);

    cout << convex_hull1.size() << " " << convex_hull2.size() << " " << convex_hull3.size()
         << " " << convex_hull4.size() << "\n";
    return hull;
}

int main(int argc, char **argv)
{

    string input = argv[1];
    string output = argv[2];

    ifstream input_file(input);
    ofstream output_file(output);

    vector<Point> data, hull;
    data.clear();
    hull.clear();

    string line;

    while (getline(input_file, line))
    {
        fflush(stdin);
        Point point = to_Point(line);
        data.push_back(point);
    }

    clock_t start, end;
    start = clock();

    hull = find_Convex_Hull(data);

    end = clock();
    cout << "Thoi gian xu li: " << (end - start) / 1000.0 << "s\n";

    for (int i = 0; i < hull.size(); i++)
        output_file << hull[i].get_x() << ", " << hull[i].get_y() << endl;

    input_file.close();
    output_file.close();

    

    return 0;
}

void find_Convex_Hull1(Point q1, Point qq1, vector<Point> &convex_hull1, vector<Point> set1)
{
    if (set1.size() == 0)
        return;
    else if (set1.size() == 1)
    {
        convex_hull1.push_back(set1[0]);
        return;
    }

    Point root;
    root.set_x(q1.get_x());
    root.set_y(qq1.get_y());

    // Tim diem xa nhat
    Point max = max_distance(set1, root);
    convex_hull1.push_back(max);

    vector<Point> new_set_1;
    vector<Point> new_set_2;

    for (int i = 0; i < set1.size(); i++)
    {
        if (set1[i].is_inside(q1, max))
            new_set_1.push_back(set1[i]);

        if (set1[i].is_inside(max, qq1))
            new_set_2.push_back(set1[i]);
    }

    // De quy lai thuat toan
    find_Convex_Hull1(q1, max, convex_hull1, new_set_1);
    find_Convex_Hull1(max, qq1, convex_hull1, new_set_2);
}

void find_Convex_Hull2(Point q2, Point qq2, vector<Point> &convex_hull2, vector<Point> set2)
{
    if (set2.size() == 0)
        return;
    else if (set2.size() == 1)
    {
        convex_hull2.push_back(set2[0]);
        return;
    }

    Point root;
    root.set_x(qq2.get_x());
    root.set_y(q2.get_y());

    // Tim diem xa nhat
    Point max = max_distance(set2, root);
    convex_hull2.push_back(max);

    vector<Point> new_set_1;
    vector<Point> new_set_2;

    for (int i = 0; i < set2.size(); i++)
    {
        if (set2[i].is_inside(q2, max))
            new_set_1.push_back(set2[i]);

        if (set2[i].is_inside(max, qq2))
            new_set_2.push_back(set2[i]);
    }

    // De quy lai thuat toan
    find_Convex_Hull2(q2, max, convex_hull2, new_set_1);
    find_Convex_Hull2(max, qq2, convex_hull2, new_set_2);
}

void find_Convex_Hull3(Point q3, Point qq3, vector<Point> &convex_hull3, vector<Point> set3)
{
    if (set3.size() == 0)
        return;
    else if (set3.size() == 1)
    {
        convex_hull3.push_back(set3[0]);
        return;
    }

    Point root;
    root.set_x(q3.get_x());
    root.set_y(qq3.get_y());

    // Tim diem xa nhat
    Point max = max_distance(set3, root);
    convex_hull3.push_back(max);

    vector<Point> new_set_1;
    vector<Point> new_set_2;

    for (int i = 0; i < set3.size(); i++)
    {
        if (set3[i].is_inside(q3, max))
            new_set_1.push_back(set3[i]);

        if (set3[i].is_inside(max, qq3))
            new_set_2.push_back(set3[i]);
    }

    // De quy lai thuat toan
    find_Convex_Hull3(q3, max, convex_hull3, new_set_1);
    find_Convex_Hull3(max, qq3, convex_hull3, new_set_2);
}

void find_Convex_Hull4(Point q4, Point qq4, vector<Point> &convex_hull4, vector<Point> set4)
{
    if (set4.size() == 0)
        return;
    else if (set4.size() == 1)
    {
        convex_hull4.push_back(set4[0]);
        return;
    }

    Point root;
    root.set_x(qq4.get_x());
    root.set_y(q4.get_y());

    // Tim diem xa nhat
    Point max = max_distance(set4, root);
    convex_hull4.push_back(max);

    vector<Point> new_set_1;
    vector<Point> new_set_2;

    for (int i = 0; i < set4.size(); i++)
    {
        if (set4[i].is_inside(q4, max))
            new_set_1.push_back(set4[i]);

        if (set4[i].is_inside(max, qq4))
            new_set_2.push_back(set4[i]);
    }

    // De quy lai thuat toan
    find_Convex_Hull4(q4, max, convex_hull4, new_set_1);
    find_Convex_Hull4(max, qq4, convex_hull4, new_set_2);
}
