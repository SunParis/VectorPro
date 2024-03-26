# include <iostream>
# include "my_vector.h"

using namespace std;
int main() {
    int pos = 0;
    int data = 0;
    fakeskiplist test(sizeof(int));
    for (int i = 0; i < 20; i++) {
        test.insert(&data, -1);
        data++;
    }
# ifdef DEBUG
    test.show();
    // test.show_2();
# endif
    data = 7;
    cin >> pos;
    while (pos >= 0) {
        int *dat = (int *)test.get(pos);
        cout << *dat << endl;
        test.edit(&data, pos);
        dat = (int *)test.get(pos);
        cout << *dat << endl;
# ifdef DEBUG
        // test.show();
        // test.show_2();
# endif
        cin >> pos;
        // data++;
    }
    test.removeall();
    return 0;
}
