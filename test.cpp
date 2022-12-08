#include <iostream>

using namespace std;

int main() {
    uint8_t* data = (uint8_t*)malloc(sizeof(size_t) + 10 * 10 * sizeof(int));
    cout << sizeof(size_t) << endl;
    cout << &data << endl;
    *((size_t*)data) = 45;
    int* p = (int*)(data + 8);
    *p = 234;
    cout << *((int*)(data + 8)) << endl;
    cout << *((size_t*)data) << endl;
    free(data);
}