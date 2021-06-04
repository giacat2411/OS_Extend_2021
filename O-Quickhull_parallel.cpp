#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <math.h>
#include <omp.h>

using namespace std;

// Class bieu diem diem phang
class Point{
    float x, y;
    public:
    Point(){
        x = 0;
        y = 0;
    }

    Point(float x, float y){
        this->x = x;
        this->y = y;
    }

    float get_x(){
        return x;
    }

    float get_y(){
        return y;
    }

    void set_x(float x){
        this->x = x;
    }

    void set_y(float y){
        this->y = y;
    }

    // Diem co nam trong duong truc giao truc tiep qua a b hay khong ?
    // Nam trong -> a.x < x < b.x va a.y < y < b.y
    bool is_inside(Point a, Point b){
        float min_x = min(a.x, b.x);
        float max_x = max(a.x, b.x);
        float min_y = min(a.y, b.y);
        float max_y = max(a.y, b.y);

        if ((min(a.x, b.x) < this->x) && (max(a.x,b.x) > this->x)
            && (min(a.y, b.y) < this->y) && (max(a.y, b.y) > this->y))
        return true;
        return false;
    }

    void print_Point(){
        std::cout<<"("<<this->x<<","<<this->y<<") ";
    }

    bool operator==(Point other){
        return ((abs(x - other.x) == 0) && (abs(y - other.y)) == 0);
    }

    bool operator!=(Point other){
        return ((x != other.x) || (y != other.y));
    }

    Point& operator=(const Point& other){
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
};

// Chuyen mot xau thanh cap diem x y
// Vd: Input = "3.4, 2.7"
// Output: (Point)(3.4;2.7)
Point to_Point(string line){
    int i = 0;
    string x, y;
    float to_x, to_y;

    x = y = "";

    while (line[i] != ','){
        x += line[i];
        i++;
    }

    i++;
    
    for(int j = i; j < line.length(); j++)
        y += line[j];
        
    while (x.find(' ') != -1) x.erase(x.begin() + x.find(' '));
    while (y.find(' ') != -1) y.erase(y.begin() + y.find(' '));

    to_x = stof(x);
    to_y = stof(y);

    Point convert(to_x, to_y);

    return convert;
}


// Tim diem highest leftmost
Point hi_le(vector<Point> points){
    vector<Point> leftmost;

    float min_x = points[0].get_x();
    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < points.size(); i++)
                if (points[i].get_x() < min_x) min_x = points[i].get_x();
    }
    
    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < points.size(); i++)
                if (points[i].get_x() == min_x) leftmost.push_back(points[i]);
    }

    Point highest = leftmost[0];

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < leftmost.size(); i++)
                if (leftmost[i].get_y() > highest.get_y()) highest = leftmost[i];
    }
    return highest;
}

// Tim diem leftmost highest
Point le_hi(vector<Point> points){
    vector<Point> highest;

    float max_y = points[0].get_y();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < points.size(); i++)
                if (points[i].get_y() > max_y) max_y = points[i].get_y();
    }

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < points.size(); i++)
                if (points[i].get_y() == max_y) highest.push_back(points[i]);
    }
    Point leftmost = highest[0];

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < highest.size(); i++)
                if (highest[i].get_x() < leftmost.get_x()) leftmost = highest[i];
    }
    return leftmost;
}

// Tim diem lowest leftmost
Point lo_le(vector<Point> points){
    vector<Point> leftmost;

    float min_x = points[0].get_x();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < points.size(); i++)
                if (points[i].get_x() < min_x) min_x = points[i].get_x();
    }

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < points.size(); i++)
                if (points[i].get_x() == min_x) leftmost.push_back(points[i]);
    }

    Point lowest = leftmost[0];

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < leftmost.size(); i++)
                if (leftmost[i].get_y() < lowest.get_y()) lowest = leftmost[i];
    }

    return lowest;
}

// Tim diem leftmost lowest
Point le_lo(vector<Point> points){
    vector<Point> lowest;

    float min_y = points[0].get_y();
    
    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < points.size(); i++)
                if (points[i].get_y() < min_y) min_y = points[i].get_y();
    }

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < points.size(); i++)
                if (points[i].get_y() == min_y) lowest.push_back(points[i]);
    }

    Point leftmost = lowest[0];
    
    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < lowest.size(); i++)
                if (lowest[i].get_x() < leftmost.get_x()) leftmost = lowest[i];
    }

    return leftmost;
}

// Tim diem lowest rightmost
Point lo_ri(vector<Point> points){
    vector<Point> rightmost;

    float max_x = points[0].get_x();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < points.size(); i++)
                if (points[i].get_x() > max_x) max_x = points[i].get_x();
    }

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < points.size(); i++)
                if (points[i].get_x() == max_x) rightmost.push_back(points[i]);
    }

    Point lowest = rightmost[0];

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < rightmost.size(); i++)
                if (rightmost[i].get_y() < lowest.get_y()) lowest = rightmost[i];
    }

    return lowest;
}

// Tim diem rightmost lowest
Point ri_lo(vector<Point> points){
    vector<Point> lowest;

    float min_y = points[0].get_y();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < points.size(); i++)
                if (points[i].get_y() < min_y) min_y = points[i].get_y();
    }

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < points.size(); i++)
                if (points[i].get_y() == min_y) lowest.push_back(points[i]);
    }

    Point rightmost = lowest[0];
    
    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < lowest.size(); i++)
                if (lowest[i].get_x() > rightmost.get_x()) rightmost = lowest[i];
    }

    return rightmost;
}

// Tim diem highest rightmost
Point hi_ri(vector<Point> points){
    vector<Point> rightmost;

    float max_x = points[0].get_x();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < points.size(); i++)
                if (points[i].get_x() > max_x) max_x = points[i].get_x();
    }

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < points.size(); i++)
                if (points[i].get_x() == max_x) rightmost.push_back(points[i]);
    }

    Point highest = rightmost[0];

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < rightmost.size(); i++)
                if (rightmost[i].get_y() > highest.get_y()) highest = rightmost[i];
    }

    return highest;
}

// Tim diem rightmost highest
Point ri_hi(vector<Point> points){
    vector<Point> highest;

    float max_y = points[0].get_y();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < points.size(); i++)
                if (points[i].get_y() > max_y) max_y = points[i].get_y();
    }

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < points.size(); i++)
                if (points[i].get_y() == max_y) highest.push_back(points[i]);
    }

    Point rightmost = highest[0];
    
    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 1; i < highest.size(); i++)
                if (highest[i].get_x() > rightmost.get_x()) rightmost = highest[i];
    }
    
    return rightmost;
}

// Noi hai vector lai voi nhau
// Input: a b
// Ouput: c = a + b
vector<Point> plus_vector(vector<Point> set1, vector<Point> set2){
    vector<Point> result;

    for (int i = 0; i < set1.size(); i++)
        result.push_back(set1[i]);

    for (int i = 0; i < set2.size(); i++)
        result.push_back(set2[i]);

    return result;   
}

// Kiem tra xem tap diem co hai diem trung nhau hay khong
// Neu co, xoa diem trung
void check(vector<Point>& points){
    for (int i = 0; i < points.size(); i++)
        for (int j = i + 1; j < points.size(); j++)
            if (points[i] == points[j]){
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
void find_Convex_Hull1(Point q1, Point qq1, vector<Point>& convex_hull1, vector<Point> set1);

// Tuong tu mien 1
void find_Convex_Hull2(Point q2, Point qq2, vector<Point>& convex_hull2, vector<Point> set2);
void find_Convex_Hull3(Point q3, Point qq3, vector<Point>& convex_hull3, vector<Point> set3);
void find_Convex_Hull4(Point q4, Point qq4, vector<Point>& convex_hull4, vector<Point> set4);

// Tim bao loi cua mot tap diem
// Input: points: tap diem
// Output: Vector chua cac diem thuoc bao loi
vector<Point> find_Convex_Hull(vector<Point> points){
    vector<Point> hull;
    hull.clear();
    
    //Tim 8 diem dac biet cua tap diem
    Point highest_leftmost, leftmost_highest, lowest_leftmost, leftmost_lowest
            , lowest_rightmost, rightmost_lowest, highest_rightmost, rightmost_highest;
            
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
                highest_leftmost = hi_le(points);                 // Convex_hull 1 
            #pragma omp section
                leftmost_highest = le_hi(points);
            #pragma omp section
                lowest_leftmost = lo_le(points);                  // Convex_hull 2
            #pragma omp section
                leftmost_lowest = le_lo(points);
            #pragma omp section
                lowest_rightmost  = lo_ri(points);                // Convex_hull 3
            #pragma omp section
                rightmost_lowest = ri_lo(points);
            #pragma omp section
                highest_rightmost = hi_ri(points);                // Convex_hull 4
            #pragma omp section
                rightmost_highest = ri_hi(points);
        }
    }

    vector<Point> convex_hull1, convex_hull2
                , convex_hull3, convex_hull4;               // Tap cac diem cuc bien 4 mien 
    vector<Point> set1, set2, set3, set4;                   // Tap diem cua 4 mien do

    convex_hull1.clear();
    convex_hull2.clear();
    convex_hull3.clear();
    convex_hull4.clear();

    set1.clear();
    set2.clear();
    set3.clear();
    set4.clear();

    // TIM CAC DIEM THUOC MIEN
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
                if (highest_leftmost == leftmost_highest) convex_hull1.push_back(highest_leftmost);
                else {
                    convex_hull1.push_back(highest_leftmost);
                    convex_hull1.push_back(leftmost_highest);

                    for (int i = 0; i < points.size(); i++)
                        if (points[i].is_inside(highest_leftmost, leftmost_highest))
                            set1.push_back(points[i]);    
                
                }
            #pragma omp section
                if (lowest_leftmost == leftmost_lowest) convex_hull2.push_back(lowest_leftmost);
                else {
                    convex_hull2.push_back(lowest_leftmost);
                    convex_hull2.push_back(leftmost_lowest);

                    for (int i = 0; i < points.size(); i++)
                        if (points[i].is_inside(lowest_leftmost, leftmost_lowest))
                            set2.push_back(points[i]);            
                }
            #pragma omp section
                if (lowest_rightmost == rightmost_lowest) convex_hull3.push_back(lowest_rightmost);
                else {
                    convex_hull3.push_back(lowest_rightmost);
                    convex_hull3.push_back(rightmost_lowest);

                    for (int i = 0; i < points.size(); i++)
                        if (points[i].is_inside(lowest_rightmost, rightmost_lowest))
                            set3.push_back(points[i]);            
                }
            #pragma omp section
                if (highest_rightmost == rightmost_highest) convex_hull4.push_back(highest_rightmost);
                else {
                    convex_hull4.push_back(highest_rightmost);
                    convex_hull4.push_back(rightmost_highest);

                    for (int i = 0; i < points.size(); i++)
                        if (points[i].is_inside(highest_rightmost, rightmost_highest))
                            set4.push_back(points[i]);            
                }
        }
    }


    // TIM CAC DIEM THUOC BAO LOI CUA 4 MIEN
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
                find_Convex_Hull1(leftmost_highest, highest_leftmost, convex_hull1, set1);
            #pragma omp section
                find_Convex_Hull2(lowest_leftmost, leftmost_lowest, convex_hull2, set2);
            #pragma omp section
                find_Convex_Hull3(rightmost_lowest, lowest_rightmost, convex_hull3, set3);
            #pragma omp section
                find_Convex_Hull4(highest_rightmost, rightmost_highest, convex_hull4, set4);
        }
    }

    // LOAI CAC DIEM TRUNG NHAU
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
                check(convex_hull1);
            #pragma omp section
                check(convex_hull2);
            #pragma omp section
                check(convex_hull3);
            #pragma omp section
                check(convex_hull4);
        }
    }

    hull = plus_vector(convex_hull1, convex_hull2);
    hull = plus_vector(hull, convex_hull3);
    hull = plus_vector(hull, convex_hull4);
    
    std::cout<<convex_hull1.size()<<" "<<convex_hull2.size()<<" "<<convex_hull3.size()
        <<" "<<convex_hull4.size()<<"\n";
    return hull;
}


int main(int argc, char** argv){
    clock_t start, end;
    start = clock();

    string input = argv[1];
    string output = argv[2];

    ifstream input_file(input);
    ofstream output_file(output);

    vector<Point> data, hull;
    data.clear();
    hull.clear();

    string line;

    while(getline(input_file, line)){
        fflush(stdin);
        Point point = to_Point(line);
        data.push_back(point);
    }

    hull = find_Convex_Hull(data);

    for (int i = 0; i < hull.size(); i++)
        output_file << hull[i].get_x() <<", "<<hull[i].get_y()<<endl;
    
    input_file.close();
    output_file.close();

    end = clock();

    std::cout<<"Thoi gian xu li: "<<(end - start)/1000.0<<"s\n";

    return 0;
}

void find_Convex_Hull1(Point q1, Point qq1, vector<Point>& convex_hull1, vector<Point> set1){
    check(convex_hull1);
    if (set1.size() == 0) return;
    else if (set1.size() == 1){
        convex_hull1.push_back(set1[0]);
        return;
    }

    // Tim hai diem dac biet moi

    Point new_q1 = le_hi(set1);
    Point new_qq1 = hi_le(set1);

    convex_hull1.push_back(new_q1);
    convex_hull1.push_back(new_qq1);

    vector<Point> new_set;
    new_set.clear();

    // Tim cac diem thuoc mien moi
    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < set1.size(); i++)
                if (set1[i].is_inside(new_q1, new_qq1)) new_set.push_back(set1[i]);
    }
    
    // De quy lai thuat toan
    find_Convex_Hull1(new_q1, new_qq1, convex_hull1, new_set);
}

void find_Convex_Hull2(Point q2, Point qq2, vector<Point>& convex_hull2, vector<Point> set2){
    check(convex_hull2);
    if (set2.size() == 0) return;
    else if (set2.size() == 1){
        convex_hull2.push_back(set2[0]);
        return;
    }

    Point new_q2 = lo_le(set2);
    Point new_qq2 = le_lo(set2);

    convex_hull2.push_back(new_q2);
    convex_hull2.push_back(new_qq2);

    vector<Point> new_set;
    new_set.clear();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < set2.size(); i++)
                if (set2[i].is_inside(new_q2, new_qq2)) new_set.push_back(set2[i]);
    }

    find_Convex_Hull2(new_q2, new_qq2, convex_hull2, new_set);
}

void find_Convex_Hull3(Point q3, Point qq3, vector<Point>& convex_hull3, vector<Point> set3){
    check(convex_hull3);
    if (set3.size() == 0) return;
    else if (set3.size() == 3){
        convex_hull3.push_back(set3[0]);
        return;
    }

    Point new_q3 = ri_lo(set3);
    Point new_qq3 = lo_ri(set3);

    convex_hull3.push_back(new_q3);
    convex_hull3.push_back(new_qq3);

    vector<Point> new_set;
    new_set.clear();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < set3.size(); i++)
                if (set3[i].is_inside(new_q3, new_qq3)) new_set.push_back(set3[i]);
    }

    find_Convex_Hull3(new_q3, new_qq3, convex_hull3, new_set);
}

void find_Convex_Hull4(Point q4, Point qq4, vector<Point>& convex_hull4, vector<Point> set4){
    check(convex_hull4);
    if (set4.size() == 0) return;
    else if (set4.size() == 1){
        convex_hull4.push_back(set4[0]);
        return;
    }

    Point new_q4 = hi_ri(set4);
    Point new_qq4  = ri_hi(set4);

    convex_hull4.push_back(new_q4);
    convex_hull4.push_back(new_qq4);

    vector<Point> new_set;
    new_set.clear();

    #pragma omp parallel
    {
        #pragma omp for nowait
            for (int i = 0; i < set4.size(); i++)
                if (set4[i].is_inside(new_q4, new_qq4)) new_set.push_back(set4[i]);
    }

    find_Convex_Hull4(new_q4, new_qq4, convex_hull4, new_set);
}
