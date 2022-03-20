// simple calculator; version 1
#include <iostream>

using namespace std;

int main() {
    try {
        int c;
        double num_1, num_2, res;
        char op;

        for (;;) {
            cout << "> ";
            if ((c = cin.get()) != EOF)
                cin.putback(c);
            else
                break;
            if (cin >> num_1 >> op >> num_2) {
                switch (op) {
                case '+':
                    res = num_1 + num_2;
                    break;
                case '-':
                    res = num_1 - num_2;
                    break;
                case '*':
                    res = num_1 * num_2;
                    break;
                case '/':
                    res = num_1 / num_2;
                    break;
                default:
                    throw runtime_error("invalid operator");
                }
                cin.get();  // read newline
                cout << "= " << res << '\n';
            } else
                throw runtime_error("invalid number");
        }
        return 0;
    } catch (exception &e) {
        cout << "Error: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cout << "Unknown error\n";
        return 2;
    }
}
