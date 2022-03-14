

#ifndef SIAOD4_SHOPREGISTER_H
#define SIAOD4_SHOPREGISTER_H
#include <vector>
using namespace std;

struct register_static{
    int cur_size=0;
    static const int max_n=100;
    int num[max_n];
    int barcode[max_n];
    int quantity[max_n];
    double price[max_n];
    double discount[max_n];
    double total[max_n];
};
struct register_dynamic{
    int cur_size=0;
    int max_n;
    int* num = new int[0];
    int* barcode= new int[0];
    int* quantity= new int[0];
    double* price= new double[0];
    double* discount= new double[0];
    double* total= new double [0];
};

struct register_vector{
    int cur_size=0;
    int max_n;
    vector <int> num;
    vector <int> barcode;
    vector <int> quantity;
    vector <double> price;
    vector <double> discount;
    vector <double> total;
};

#endif //SIAOD4_SHOPREGISTER_H
