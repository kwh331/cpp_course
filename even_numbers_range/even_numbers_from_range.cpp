#include <iostream>

using namespace std;

int main() {
    int a, b;
    cout << "Enter the lower bound.\n";
    cin >> a;
    cout << "Enter the upper bound.\n";
    cin >> b;
    if (a < b){
        cout << "All even numbers between "<< a<< " and " << b <<  " are: \n";
        for (int i = a; i <= b; ++i) {
            if (i % 2 == 0)
                cout << i << ' ';
        }
    }
    else cout << "No even number between a and b.\n";
    return 0;
}
