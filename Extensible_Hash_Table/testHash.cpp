#include "ExtensibleHashTable.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
    ExtensibleHashTable A;
    cout<< "create" << endl;
    cout << "insert 10" << endl;
    A.insert(10);
    A.print();
    cout << "insert 8" <<endl;
    A.insert(8);
    A.print();
    cout << "insert 16" << endl;
    A.insert(16);
    A. print();
    cout << "insert 2" << endl;
    A.insert(2);
    A.print();
    cout << "insert 12" << endl;
    A.insert(12);
    A.print();
    cout << "insert 3:" << endl;
    A.insert(3);
    A.print();
    cout << "insert 5:" << endl;
    A.insert(5);
    A.print();
    cout << "insert 7:" << endl;
    A.insert(7);
    A.print();
    /*cout << "remove 224: " << A.remove(224) << endl;
    A.print();*/
    return 0;
}
