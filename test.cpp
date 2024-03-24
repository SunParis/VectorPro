# include <iostream>
# include "my_vector.h"

using namespace std;
int main() {
    int pos = 0;
    int data = 0;
    fakeskiplist test(sizeof(int));
    for (int i = 0; i < 20; i++) {
        test.insert(&data, -1);
    }
    test.show();
    cin >> pos;
    while (pos != -1) {
        test.remove(pos);
        test.show();
        cin >> pos;
    }
    test.Destroyall();
    return 0;
}
