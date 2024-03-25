# include <iostream>
# include "my_vector.h"

using namespace std;
int main() {
    int pos = 0;
    int data = 0;
    fakeskiplist test(sizeof(int));
    for (int i = 0; i < 6; i++) {
        test.insert(&data, -1);
    }
# ifdef DEBUG
    test.show();
    test.show_2();
# endif
    cin >> pos;
    while (pos >= 0) {
        test.insert(&data, -1);
# ifdef DEBUG
        test.show();
        test.show_2();
# endif
        cin >> pos;
    }
    test.Destroyall();
    return 0;
}
