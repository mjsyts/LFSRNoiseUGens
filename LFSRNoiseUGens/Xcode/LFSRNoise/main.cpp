// Created 7/23/23
// m. josiah sytsma

#include <iostream>
#include <bitset>
using namespace std;

int main() {
    for (int i = 0; i <= 32; i++){
        cout<<bitset<32>(~(~0u << i))<<"\n";
    };
}
