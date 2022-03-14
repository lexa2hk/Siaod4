#include <iostream>
#include <windows.h>
#include <iomanip>
#include "ShopRegister.h"
using namespace std;

void printReg(register_static &reg,int reg_index){
    cout<<"num "<<"code "<<"Q "<<"price "<<"disc "<<"total"<<endl;
    for(int i=0;i<reg.cur_size;i++){
        reg.total[i] = reg.quantity[i]*reg.price[i]*(1+ (reg.discount[i]/100.0));
        if(reg_index == reg.num[i]) cout<<reg.num[i]<<" "<<reg.barcode[i]<<" "<<reg.quantity[i]<<" "<<reg.price[i]<<" "<<reg.discount[i]<<" "<<reg.total[i]<<endl;
    }
}

void addNote(register_static &reg){
    if(reg.cur_size>=99){
        cerr<<"Size error";
        return;
    }
    cout<<"Введите номер кассы, код товара, количество, цену и скидку\n";
    cin>>reg.num[reg.cur_size]>>reg.barcode[reg.cur_size]>>reg.quantity[reg.cur_size]>>reg.price[reg.cur_size]>>reg.discount[reg.cur_size];
    reg.cur_size++;
}
void insertNote(register_static &reg,int reg_index){

    if(reg.cur_size>=99){
        cerr<<"Size error";
        return;
    }
    for(int i=0;i<reg.cur_size;i++){
        if(reg.num[i]==reg_index){
            //move + insert
            for(int j = reg.cur_size+1;j>i;j--){
                swap(reg.num[j],reg.num[j-1]);
                swap(reg.barcode[j],reg.barcode[j-1]);
                swap(reg.quantity[j],reg.quantity[j-1]);
                swap(reg.price[j],reg.price[j-1]);
                swap(reg.discount[j],reg.discount[j-1]);
                swap(reg.total[j],reg.total[j-1]);
            }
            cout<<"Введите код товара, количество, цену и скидку\n";
            reg.num[i] = reg_index;
            cin>>reg.barcode[i]>>reg.quantity[i]>>reg.price[i]>>reg.discount[i];
            reg.cur_size++;
            break;
        }

    }
}

void delReg(register_static &reg,int reg_index){
    for(int i=0;i<reg.cur_size;i++){
        if(reg_index == reg.num[i]){
            //move + reduce size
            for(int j=i;j<reg.cur_size;j++){
                if(!(reg.cur_size==99 && j==99)){
                    swap(reg.num[j],reg.num[j+1]);
                    swap(reg.barcode[j],reg.barcode[j+1]);
                    swap(reg.quantity[j],reg.quantity[j+1]);
                    swap(reg.price[j],reg.price[j+1]);
                    swap(reg.discount[j],reg.discount[j+1]);
                    swap(reg.total[j],reg.total[j+1]);
                }
            }
            i--;
            reg.cur_size--;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    register_static reg;
    addNote(reg);
    addNote(reg);
    addNote(reg);

    cout<<"Введите номер кассы, для которой нужно вставить запись\n";
    int reg_index;
    cin>>reg_index;
    insertNote(reg,reg_index);

    printReg(reg, 1);
    delReg(reg,1);
    printReg(reg, 1);
    return 0;
}
