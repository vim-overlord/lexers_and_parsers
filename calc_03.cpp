// simple calculator; version 3
#include <iostream>
#include <vector>

using namespace std;

constexpr char num = '0';   // can be any char

class Terminate {};

class Token {
public:
    int type;
    double val;
    // for operators, parentheses, and newlines
    Token(char c) : type(c), val(0) {}
    Token(double d) : type(num), val(d) {}    // for numbers
};

class Tstream {
public:
    Token get();           // returns next Token
    void putback(Token t); // puts Token back
private:
    bool full {};       // whether buffer is full
    Token buffer {0};   // buffer for putback
};

Token Tstream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    int c;
    c = cin.get();
    switch (c) {
    case EOF:
        throw Terminate();
    case ' ': case '\t':
        return get();   // skip whitespace
    case '(': case ')': case '+': case '-': case '*': case '/': case '\n':
        return Token(c);
    case '.': case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9': {
        cin.putback(c);
        double d;
        cin >> d;
        return Token(d);
    }
    default:
        throw runtime_error("get: invalid token");
    }
}

void Tstream::putback(Token t) {
    if (full)
        throw runtime_error("putback: full buffer");
    buffer = t;
    full = true;
}

int parens;
Tstream ts;
double expression();

double primary() {
    Token t = ts.get();

    switch (t.type) {
    case '(': {
        ++parens;
        double d = expression();

        t = ts.get();
        if (t.type != ')')
            throw runtime_error("')' expected");
        --parens;
        return d;
    }
    case '+':   // deal with signs
        t = ts.get();
        if (t.type != num)
            throw runtime_error("primary expected");
        return t.val;
    case '-':
        t = ts.get();
        if (t.type != num)
            throw runtime_error("primary expected");
        return -t.val;
    case num:
        return t.val;
    default:
        throw runtime_error("primary expected");
    }
}

double term() {
    double d = primary();
    
    for (;;) {
        Token t = ts.get();

        switch (t.type) {
        case '*':
            d *= primary();
            break;
        case '/': {
            double temp = primary();

            if (temp == 0)
                throw runtime_error("divide by zero");
            d /= temp;
            break;
        }
        default:
            if (t.type == num)
                throw runtime_error("missing operator");
            else if (t.type == ')' && parens <= 0)
                throw runtime_error("trailing ')'");
            ts.putback(t);
            return d;
        }
    }
}

double expression() {
    double d = term();

    for (;;) {
        Token t = ts.get();

        switch (t.type) {
        case '+':
            d += term();
            break;
        case '-':
            d -= term();
            break;
        case '\n':  // don't putback newline
            return d;
        default:
            ts.putback(t);
            return d;
        }
    }
}

int main() {
    try {
        for (;;) {
            cout << "> ";
            double res {expression()};

            cout << "= " << res << '\n';
        }
    } catch (Terminate) {
        return 0;
    } catch (exception &e) {
        cout << "Error: " << e.what() << '\n';
        return 1;
    } catch (...) {
        cout << "Unknown error\n";
        return 2;
    }
}
