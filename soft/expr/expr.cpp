// This is example from Bjarne Stroustrup The C++ Programming Language 3ed

#include <string>
#include <map>
#include <iostream>
#include <cctype>

using namespace std;

enum Token_value {
  NAME, NUMBER, END,
  PLUS ='+', MINUS = '-', MUL = '*', DIV = '/',
  EOL = ';', ASSIGN = '=', LP = '(', RP = ')'
};

Token_value curr_token = EOL;
map<string, double> table;
double num_value;
string str_value;
int no_of_errors = 0;

Token_value get_token();

double term(bool get);
double expr(bool get);
double prim(bool get);
int error(const string& s);


double expr(bool get) {
  double left = term(get);

  for (;;) {
    switch (curr_token) {
      case PLUS:
        left += term(true);
        break;
      case MINUS:
        left -= term(true);
        break;
      default:
        return left;
    }
  }
}

double term(bool get) {
  double left = prim(get);

  for (;;) {
    switch (curr_token) {
      case MUL:
        left *= term(true);
        break;
      case DIV:
        if (double d = prim(true)) {
          left /= d;
          break;
        }
        return error("Division by zero");
      default:
        return left;
    }
  }
}

double prim(bool get) {
  if (get)
    get_token();

  switch (curr_token) {
    case NUMBER: {
      double v = num_value;
      get_token();
      return v;
    }

    case NAME: {
      double& v = table[str_value];
      if (get_token() == ASSIGN)
        v = expr(true);
      return v;
    }

    case MINUS:
      return -prim(true);

    case LP: {
      double e = expr(true);
      if (curr_token != RP)
        return error("waiting )");
      get_token();  // skip )
      return e;
    }

    default:
      return error("waiting for primary value");
  }
}

Token_value get_token() {
  char ch;
  do {
    if (!cin.get(ch))
      return curr_token = END;
  } while (ch != '\n' && isspace(ch));

  switch (ch) {
    case 0:
      return curr_token = END;

    case ';':
    case '\n':
      return curr_token = EOL;

    case '*': case '/': case '+': case '-':
    case '(': case ')': case '=':
      return curr_token = Token_value(ch);

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
      cin.putback(ch);
      cin >> num_value;
      return curr_token = NUMBER;

    default:
      if (isalpha(ch)) {
        str_value = ch;
        while (cin.get(ch) && isalnum(ch))
          str_value += ch;
        cin.putback(ch);
        return curr_token = NAME;
      }
      error("wrong lexeme");
      return curr_token = EOL;
  }
}

int error(const string& s) {
  no_of_errors++;
  cerr << "error: " << s << endl;
  return 1;
}

int main() {
  table["PI"] = 3.1415926;
  table["e"]  = 2.7182818;

  while (cin) {
    get_token();
    if (curr_token == END)
      break;
    if (curr_token == EOL)
      continue;

    cout << expr(false) << endl;
  }

  return no_of_errors;
}
