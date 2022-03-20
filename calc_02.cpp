// simple calculator; version 2 (does not follow order of operations)
#include <iostream>

using namespace std;

int main() {
    try {
        int c;
        double num_1, num_2;
        char op;

        for (;;) {
            cout << "> ";
            if ((c = cin.get()) != EOF)
                cin.putback(c);
            else
                break;
            if (!(cin >> num_1))
                throw runtime_error("invalid number");
            while ((c = cin.get()) != '\n') {
                cin.putback(c);
                if (!(cin >> op >> num_2))
                    throw runtime_error("invalid number");
                switch (op) {
                case '+':
                    num_1 += num_2;
                    break;
                case '-':
                    num_1 -= num_2;
                    break;
                case '*':
                    num_1 *= num_2;
                    break;
                case '/':
                    num_1 /= num_2;
                    break;
                default:
                    throw runtime_error("invalid operator");
                }
            }
            cout << "= " << num_1 << '\n';
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
