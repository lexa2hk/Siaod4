

#ifndef SIAOD4_SHOPREGISTER_H
#define SIAOD4_SHOPREGISTER_H

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

#endif //SIAOD4_SHOPREGISTER_H
