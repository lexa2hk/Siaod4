#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
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

//====================================DYNAMIC==================================

void regAddD(register_dynamic *reg,int index=0){
    reg->cur_size++;
    int* num = new int[reg->cur_size];
    int* barcode= new int[reg->cur_size];
    int* quantity= new int[reg->cur_size];
    double* price= new double[reg->cur_size];
    double* discount= new double[reg->cur_size];
    double* total= new double [reg->cur_size];

    for(int i=0;i<reg->cur_size;i++){
        if(i<index){
            num[i] = reg->num[i];
            quantity[i] = reg->quantity[i];
            barcode[i] = reg->barcode[i];
            price[i] = reg->price[i];
            discount[i] = reg->discount[i];
            total[i] = reg->total[i];
        }else if(i==index){
            cout<<"Введите номер кассы, код товара, количество, цену и скидку\n";
            cin>>num[i]>>quantity[i]>>barcode[i]>>price[i]>>discount[i];
        }else{
            num[i+1] = reg->num[i];
            quantity[i+1] = reg->quantity[i];
            barcode[i+1] = reg->barcode[i];
            price[i+1] = reg->price[i];
            discount[i+1] = reg->discount[i];
            total[i+1] = reg->total[i];
        }
    }
    reg->num = num;
    reg->barcode = barcode;
    reg->quantity = quantity;
    reg->price = price;
    reg->discount = discount;
    reg->total = total;
}

void regPopD(register_dynamic *reg,int index=0){
    reg->cur_size--;
    int* num = new int[reg->cur_size];
    int* barcode= new int[reg->cur_size];
    int* quantity= new int[reg->cur_size];
    double* price= new double[reg->cur_size];
    double* discount= new double[reg->cur_size];
    double* total= new double [reg->cur_size];

    for(int i=0;i<reg->cur_size;i++){
        if(i<index){
            num[i] = reg->num[i];
            quantity[i] = reg->quantity[i];
            barcode[i] = reg->barcode[i];
            price[i] = reg->price[i];
            discount[i] = reg->discount[i];
            total[i] = reg->total[i];
        }else{
            num[i] = reg->num[i+1];
            quantity[i] = reg->quantity[i+1];
            barcode[i] = reg->barcode[i+1];
            price[i] = reg->price[i+1];
            discount[i] = reg->discount[i+1];
            total[i] = reg->total[i+1];
        }
    }
    reg->num = num;
    reg->barcode = barcode;
    reg->quantity = quantity;
    reg->price = price;
    reg->discount = discount;
    reg->total = total;
}

void printRegD(register_dynamic &reg,int reg_index){
    cout<<"num "<<"code "<<"Q "<<"price "<<"disc "<<"total"<<endl;
    for(int i=0;i<reg.cur_size;i++){
        reg.total[i] = reg.quantity[i]*reg.price[i]*(1+ (reg.discount[i]/100.0));
        if(reg_index == reg.num[i]) cout<<reg.num[i]<<" "<<reg.barcode[i]<<" "<<reg.quantity[i]<<" "<<reg.price[i]<<" "<<reg.discount[i]<<" "<<reg.total[i]<<endl;
    }
}

void insertD(register_dynamic *reg,int num){
    for(int i=0;i<reg->cur_size;i++){
        if(reg->num[i] == num) regAddD(reg, i);
    }
}
void removeRegD(register_dynamic *reg,int num){
    for(int i=0;i<reg->cur_size;i++){
        if(reg->num[i] == num) regPopD(reg, i);
    }
}

//================================VECTOR========================
void addRowV(register_vector &reg){
    reg.cur_size++;
    cout<<"Введите номер кассы, код товара, количество, цену и скидку\n";
    int temp;
    cin>>temp;
    reg.num.push_back(temp);
    cin>>temp;
    reg.barcode.push_back(temp);
    cin>>temp;
    reg.quantity.push_back(temp);

    double tempd;
    cin>>tempd;
    reg.price.push_back(temp);
    cin>>tempd;
    reg.discount.push_back(temp);
    reg.price.push_back(0);
}

void insert(register_vector &reg,int num){
    int id,code,quantuty;
    double price, discount;
    cout<<"Введите номер кассы для вставки в начало, код товара, количество, цену и скидку\n";
    cin>>id>>code>>quantuty>>price>>discount;
    for(int i=0;i<reg.num.size();i++){
        if(num==reg.num[i]) {
            reg.cur_size++;
            reg.num.insert(reg.num.begin()+i,id);
            reg.barcode.insert(reg.barcode.begin()+i,code);
            reg.quantity.insert(reg.quantity.begin()+i,quantuty);
            reg.price.insert(reg.price.begin()+i,price);
            reg.discount.insert(reg.discount.begin()+i,discount);
            reg.total.insert(reg.total.begin()+i,(quantuty*price)*(1+discount/100));
        }
    }
}
void printreg(register_vector reg,int num){
    for(int i=0;i<reg.num.size();i++){
        if(reg.num[i]==num){
            cout<<"num "<<"code "<<"Q "<<"price "<<"disc "<<"total"<<endl;
            cout<<reg.num[i]<<reg.barcode[i]<<reg.quantity[i]<<reg.price[i]<<reg.discount[i]<<reg.total[i]<<endl;
        }
    }
}

void removereg(register_vector reg, int num){
    for(int i=0;i<reg.num.size();i++){
        if(reg.num[i]==num){
            reg.cur_size--;
            reg.num.erase(reg.num.begin()+i);
            reg.barcode.erase(reg.barcode.begin()+i);
            reg.quantity.erase(reg.quantity.begin()+i);
            reg.price.erase(reg.price.begin()+i);
            reg.discount.erase(reg.discount.begin()+i);
            reg.total.erase(reg.total.begin()+i);

        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    /*register_static reg;
    addNote(reg);
    addNote(reg);
    addNote(reg);

    cout<<"Введите номер кассы, для которой нужно вставить запись\n";
    int reg_index;
    cin>>reg_index;
    insertNote(reg,reg_index);

    printReg(reg, 1);
    delReg(reg,1);
    printReg(reg, 1);*/

    /*register_dynamic reg;
    regAddD(&reg);
    printRegD(reg,1);
    regPopD(&reg,0);
    printRegD(reg,1);*/

    return 0;
}
