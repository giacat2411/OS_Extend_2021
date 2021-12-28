#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <math.h>
using namespace std;
//=========================BAT DAU CHUONG TRINH===========================//

//=========================DINH NGHIA VÀ KHAI BAO==========================//

class Point {
    float x, y;
    
public:
    Point()  { x = 0; y = 0; }
    
    Point(float x, float y) { this->x = x; this->y = y; }
    
    float get_x() { return x; }
    
    float get_y() { return y; }
    
    void set_x(float x) { this->x = x; }
    
    void set_y(float y) { this->y = y; }
    
    
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
Point to_Point(string line);
//Tim 16 diem cuc
vector<Point> Find_16_Extremes(vector<Point> points);
//Tim 8 tap tilde V
void Find_8_tilde_Sets(vector<Point> points, vector<Point>& tildeV1, vector<Point>& tildeV2, vector<Point>& tildeV3, 
                                vector<Point>& tildeV4, vector<Point>& tildeV5, vector<Point>& tildeV6, vector<Point>& tildeV7, 
                                vector<Point>& tildeV8);

// Doc du lieu
void readData(string input, vector<Point> &data);

// Ghi du lieu
void writeData(string output, vector<Point> hull);


//=======================HAM MAIN=========================//

int main(int argc, char **argv)
{
    // Doc du lieu tu file
    string input = argv[1];
    vector<Point> data;
    readData(input, data);
   
    
    //Khoi tao 8 tap Tilde V
    vector<Point> tildeV1, tildeV2, tildeV3, tildeV4, tildeV5, tildeV6, tildeV7, tildeV8;
    tildeV1.clear();
    tildeV2.clear();
    tildeV3.clear();
    tildeV4.clear();
    tildeV5.clear();
    tildeV6.clear();
    tildeV7.clear();
    tildeV8.clear();
    
    // Tinh thoi gian tim 8 tap tilde sets
    clock_t start, end;
    start = clock();
    Find_8_tilde_Sets(data, tildeV1, tildeV2, tildeV3, tildeV4, tildeV5, tildeV6, tildeV7, tildeV8);
    end = clock();
    cout << "Thoi gian tim 8 tap tilde V la: " << (end - start) / 1000.0 << "s\n";
    
    // GHI DU LIEU CUA 8 TAP RA 8 FILEs
    //string output = argv[2];
    writeData("tildeV1.csv", tildeV1);
    writeData("tildeV2.csv", tildeV2);
    writeData("tildeV3.csv", tildeV3);
    writeData("tildeV4.csv", tildeV4);
    writeData("tildeV5.csv", tildeV5);
    writeData("tildeV6.csv", tildeV6);
    writeData("tildeV7.csv", tildeV7);
    writeData("tildeV8.csv", tildeV8);
    return 0;
}

//======================KET THUC HAM MAIN=======================//



//=======================  Doc du lieu ========================//
void readData(string input, vector<Point> &data){
    data.clear();
    ifstream input_file(input);
    
    string line;
    
    while (getline(input_file, line))
    {
        fflush(stdin);
        Point point = to_Point(line);
        data.push_back(point);
    }
    input_file.close();
}
//=======================  Ghi du lieu ========================//

void writeData(string output, vector<Point> hull) {
    ofstream output_file(output);
    
    for (int i = 0; i < hull.size(); i++)
        output_file << hull[i].get_x() << ", " << hull[i].get_y() << endl;
    
    output_file.close();
}
//============== Chuyen mot xau thanh cap diem x y =================//

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

//======================= Tim 16 diem cuc ========================//
vector<Point> Find_16_extremes(vector<Point> points){
    vector<Point> tilde_v;

    for (int i = 0; i < 18; i++) tilde_v.push_back(points[0]);

    double min_e2, max_e2, min_e4, max_e4;
    double min_x = points[0].get_x();
    double max_x = points[0].get_x();
    double min_y = points[0].get_y();
    double max_y = points[0].get_y();
    double e21 =  max_y - min_y;
    double e22 =  max_x - min_x;
    double e41 =  - max_y + min_y;
    double e42 = max_x - min_x;
    
    min_e2 = max_e2 = min_e4 = max_e4 = e21*points[0].get_x() + e22*points[0].get_y();

    for (int i = 1; i < points.size(); i++){
         // Danh gia hoanh do - huong e1
        if (points[i].get_x() < min_x){
            min_x = points[i].get_x();
            tilde_v[9] = points[i]; //v5 first
            tilde_v[10] = points[i];//v5 last
        }
        else{
            if (points[i].get_x() < max_x){
                max_x = points[i].get_x();
                tilde_v[1] = points[i]; //v1 fist
                tilde_v[2] = points[i]; //v1 last
            }
            else{
                if (points[i].get_x() == min_x){
                    if (points[i].get_y() > tilde_v[9].get_y())
                        tilde_v[9] = points[i];
                    if (points[i].get_y() < tilde_v[10].get_y())
                        tilde_v[10] = points[i];
                }
                if (points[i].get_x() == max_x){
                    if (points[i].get_y() > tilde_v[2].get_y())
                        tilde_v[2] = points[i];
                    if (points[i].get_y() > tilde_v[1].get_y())
                        tilde_v[1] = points[i];
                }
            }
        }
        // Danh gia tung do - huong e3
        if (points[i].get_y() < min_y){
            min_y = points[i].get_y();
            tilde_v[13] = points[i]; //v7 first
            tilde_v[14] = points[i]; //v7last
        }
        else{
            if (points[i].get_y() > max_y){
                max_y = points[i].get_y();
                tilde_v[5] = points[i]; // v3 first
                tilde_v[6] = points[i]; // v3 last
            }
            else{
                if (points[i].get_y() == min_y){
                    if (points[i].get_x() > tilde_v[14].get_x())
                        tilde_v[14] = points[i];
                    if (points[i].get_x() < tilde_v[13].get_x())
                        tilde_v[13] = points[i];
                }
                if (points[i].get_y() == max_y){
                    if (points[i].get_x() > tilde_v[5].get_x())
                        tilde_v[5] = points[i];
                    if (points[i].get_x() < tilde_v[6].get_x())
                        tilde_v[6] = points[i];
                }
            }
        }

        //Tim cac diem cuc theo huong e2
        if (e21*points[i].get_x() + e22*points[i].get_y() < min_e2){
            min_e2 = e21*points[i].get_x() + e22*points[i].get_y();
            tilde_v[11] = points[i]; // v6 first
            tilde_v[12] = points[i]; // v6 last
        }
        else{
            if (e21*points[i].get_x() + e22*points[i].get_y() > max_e2){
                max_e2 = e21*points[i].get_x() + e22*points[i].get_y();
                tilde_v[3] = points[i]; // v2 first
                tilde_v[4] = points[i]; // v2 last
            }
            else{
                if (e21*points[i].get_x() + e22*points[i].get_y() == min_e2){
                    if (points[i].get_x() > tilde_v[12].get_x())
                        tilde_v[12] = points[i];
                    if (points[i].get_x() < tilde_v[11].get_x())
                        tilde_v[11] = points[i];
                }
                if (e21*points[i].get_x() + e22*points[i].get_y() == max_e2){
                    if (points[i].get_x() > tilde_v[3].get_x())
                        tilde_v[3] = points[i];
                    if (points[i].get_x() < tilde_v[4].get_x())
                        tilde_v[4] = points[i];
                }
            }
        }
        //Tim cac diem cuc theo huong e4
        if (e41*points[i].get_x() + e42*points[i].get_y() < min_e4)
        {
            min_e4 = e41*points[i].get_x() + e42*points[i].get_y();
            tilde_v[15] = points[i]; // v2 first
            tilde_v[16] = points[i]; // v2 last
        }
        else
        {
            if (e41*points[i].get_x() + e42*points[i].get_y() > max_e4)
            {
                max_e4 = e41*points[i].get_x() + e42*points[i].get_y();
                tilde_v[7] = points[i]; // v6 first
                tilde_v[8] = points[i]; // v6 last
            }
            else
            {
                if (e41*points[i].get_x() + e42*points[i].get_y())
                {
                    if (points[i].get_x() > tilde_v[16].get_x())
                        tilde_v[16] = points[i];
                    if (points[i].get_x() < tilde_v[15].get_x())
                        tilde_v[15] = points[i];
                }
                if (e41*points[i].get_x() + e42*points[i].get_y())
                {
                    if (points[i].get_x() > tilde_v[7].get_x())
                        tilde_v[7] = points[i];
                    if (points[i].get_x() < tilde_v[8].get_x())
                        tilde_v[8] = points[i];
                }
            }
        }
        // Xong huong e4
    }
    tilde_v[17] = tilde_v[1];
    return tilde_v;
}


//======================= Tim 8 Tap Tilde V ========================//

void Find_8_tilde_Sets(vector<Point> points, vector<Point>& tildeV1, vector<Point>& tildeV2, vector<Point>& tildeV3, 
                                vector<Point>& tildeV4, vector<Point>& tildeV5, vector<Point>& tildeV6, vector<Point>& tildeV7, 
                                vector<Point>& tildeV8)
{
    vector<Point> tilde_v = Find_16_extremes(points);

    // Luu cac diem cuc vao tam mang
    // Mang tilde V1
    if (tilde_v[2] == tilde_v[3]){
        tildeV1.push_back(tilde_v[2]);
    }
    else{
        tildeV1.push_back(tilde_v[2]);
        tildeV1.push_back(tilde_v[3]);
    }
    //Mang tilde V2
    if (tilde_v[4] == tilde_v[5])
    {
        tildeV2.push_back(tilde_v[4]);
    }
    else{
        tildeV2.push_back(tilde_v[4]);
        tildeV2.push_back(tilde_v[5]);
    }
    //Mang tilde V3
    if (tilde_v[6] == tilde_v[7]){
        tildeV3.push_back(tilde_v[6]);
    }
    else{
        tildeV3.push_back(tilde_v[6]);
        tildeV3.push_back(tilde_v[7]);
    }
    //Mang tilde V4
    if (tilde_v[8] == tilde_v[9]){
        tildeV4.push_back(tilde_v[8]);
    }
    else{
        tildeV4.push_back(tilde_v[8]);
        tildeV4.push_back(tilde_v[9]);
    }
    //Mang  tilde V5
    if (tilde_v[10] == tilde_v[11]){
        tildeV5.push_back(tilde_v[10]);
    }
    else{
        tildeV5.push_back(tilde_v[10]);
        tildeV5.push_back(tilde_v[11]);
    }
    //Mang tilde V6
    if (tilde_v[12] == tilde_v[13]){
        tildeV6.push_back(tilde_v[12]);
    }
    else{
        tildeV6.push_back(tilde_v[12]);
        tildeV6.push_back(tilde_v[13]);
    }
    //Mang tilde V7
    if (tilde_v[14] == tilde_v[15]){
        tildeV7.push_back(tilde_v[14]);
    }
    else{
        tildeV7.push_back(tilde_v[14]);
        tildeV7.push_back(tilde_v[15]);
    }
    //Mang tilde V8
    if (tilde_v[16] == tilde_v[1]){
        tildeV8.push_back(tilde_v[16]);
    }
    else{
        tildeV8.push_back(tilde_v[16]);
        tildeV8.push_back(tilde_v[1]);
        }
    /*Luu cac diem va so diem nam ben trai cac doan thang noi hai diem cuc trong moi tap vaf
     diem xa doan thang noi hai diem cuc nhat*/
    
    int j=2;
    double Ori[17], a1[17], a2[17], b[17];
    //Tinh san cac he so de giam so phep tinh co ban khi tinh Orient
    while (j<17)
    {
        a1[j] = tilde_v[j+1].get_x() - tilde_v[j].get_x();
        a2[j] = tilde_v[j+1].get_y() - tilde_v[j].get_y();
        b[j] = a1[j]*tilde_v[j+1].get_x() - a2[j] * tilde_v[j+1].get_y();
        j = j + 2;
    }
    //Tim cac diem con lai trong 8 tap tilde V
    for (int i = 0; i < points.size(); i++){
        //Tap tilde V1
        if ((points[i].get_x() >= tilde_v[3].get_x()) && (points[i].get_y()>= tilde_v[2].get_y())){
            Ori[2] = a1[2]*points[i].get_y()-a2[2]*points[i].get_x()+b[2];
            if(Ori[2]>0){
                tildeV1.push_back(points[i]);
            }
        }
        //Tap tilde V2
        else{
            if ((points[i].get_x() >= tilde_v[5].get_x()) && (points[i].get_y() >= tilde_v[4].get_y())){
                Ori[4] = a1[4]*points[i].get_y()-a2[4]*points[i].get_x()+b[4];
                if(Ori[4]>0){
                    tildeV2.push_back(points[i]);
                }
            }
            //Tap tilde V3
            else{
                if ((points[i].get_x() <= tilde_v[6].get_x()) && (points[i].get_y() >= tilde_v[7].get_y())){
                    Ori[6] = a1[6]*points[i].get_y()-a2[6]*points[i].get_x()+b[6];
                    if(Ori[6]>0){
                        tildeV3.push_back(points[i]);
                    }
                }
                //Tap tilde V4
                else{
                    if ((points[i].get_x() <= tilde_v[8].get_x()) && (points[i].get_y() >= tilde_v[9].get_y())){
                        Ori[8] = a1[8]*points[i].get_y()-a2[8]*points[i].get_x()+b[8];
                        if(Ori[8]>0){
                            tildeV4.push_back(points[i]);
                        }
                    }
                    //Tap tilde V5
                    else{
                        if ((points[i].get_x() <= tilde_v[11].get_x()) && (points[i].get_y() <= tilde_v[10].get_y())){
                            Ori[10] = a1[10]*points[i].get_y()-a2[10]*points[i].get_x()+b[10];
                            if(Ori[10]>0){
                                tildeV5.push_back(points[i]);
                            }
                        }
                        //Tap tilde V6
                        else{
                            if ((points[i].get_x() <= tilde_v[13].get_x()) && (points[i].get_y() <= tilde_v[12].get_y())){
                                Ori[12] = a1[12]*points[i].get_y()-a2[12]*points[i].get_x()+b[12];
                                if(Ori[12]>0){
                                    tildeV6.push_back(points[i]);
                                }
                            }
                            //Tap tilde V7
                            else{
                                if ((points[i].get_x() <= tilde_v[15].get_x()) && (points[i].get_y() <= tilde_v[14].get_y())){
                                    Ori[14] = a1[14]*points[i].get_y()-a2[14]*points[i].get_x()+b[14];
                                    if(Ori[14]>0){
                                        tildeV7.push_back(points[i]);
                                    }
                                }
                                //Tap tilde V8
                                else{
                                    if ((points[i].get_x() <= tilde_v[1].get_x()) && (points[i].get_y() <= tilde_v[16].get_y())){
                                        Ori[16] = a1[16]*points[i].get_y()-a2[16]*points[i].get_x()+b[16];
                                        if(Ori[16]>0){
                                            tildeV8.push_back(points[i]);
                                        }
                                    }
                                }
                            }
                            
                        }
                    }
                }
            }
            
        } //ket thuc for cua i
    }
}




