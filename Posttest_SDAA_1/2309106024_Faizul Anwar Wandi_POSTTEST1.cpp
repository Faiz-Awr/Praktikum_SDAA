#include <iostream>
using namespace std;

int faktorial(int angka){
    if(angka > 1) {
        return angka * faktorial(angka - 1);
    } else {
        return 1;
    }
}
int kombinasi(int i, int j){
    return faktorial(i) / (faktorial(j) * faktorial(i - j));
}
void segitigapascal(int baris, int i = 0){
    if (i < baris) {
        for (int j = 0; j <= i; j++) {
            cout << kombinasi(i, j) << " ";
        }
        cout << endl; 
        segitigapascal(baris, i + 1); 
    }
}

int main(){
    cout << "##       Segitiga Pascal        ##" << endl;
    cout << "==================================" << endl;
    cout << endl;
    int baris = 3;
    segitigapascal(baris);
    return 0;
}