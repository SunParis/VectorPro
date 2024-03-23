# include <iostream>
# include "my_vector.h"

using namespace std;
int main() {
    int data = 0;
    int input = -1;
    fakeskiplist test(sizeof(int));
    /*test.insert(&data, -1);
    data++;
    test.insert(&data, -1);
    data++;
    test.insert(&data, -1);
    data++;
    test.show();
    cin >> input;
    while (input > -2 && input < (int)test.length()) {
        test.insert(&data, input);
        data++;
        test.show();
        cin >> input;
    }
    cout << input << endl;*/
    test.Destroyall();
    return 0;
}
