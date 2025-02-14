#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

string input;
int pos = 0;

void esperaCaracter(char esperado);
char siguienteCaracter();
double encuentraNumero();
double factor();
double terminal();
double expresion();

// Cambiar de caracterer y evitar salirse
void esperaCaracter(char esperado) {
    if (pos < input.size() && input[pos] == esperado || isspace(input[pos]) ) {
        pos++;
    } else {
        throw runtime_error("Error se esperaba '" + string(1, esperado) + "' en la posicion " + to_string(pos));
    }
}

// Se ve si se llega al flag para poner la fin de línea
char siguienteCaracter() {
    while (pos < input.size() && isspace(input[pos])) {
        pos++;
    }
    return (pos < input.size()) ? input[pos] : '\0';
}
//Se busca el número completo
double encuentraNumero() {
    string numStr;
    while (isdigit(siguienteCaracter()) || siguienteCaracter() == '.') {
        numStr += siguienteCaracter();
        esperaCaracter(siguienteCaracter());
    }
    return stod(numStr);
}

double factor() {
    if (isdigit(siguienteCaracter())) {
        return encuentraNumero();
    } else if (siguienteCaracter() == '(') {
        esperaCaracter('(');
        double result = expresion();
        esperaCaracter(')');
        return result;
    }  else {
        throw runtime_error("Error se esperaba un numero o '(' en la posicion " + to_string(pos));
    }
}

// Multiplicacion y division
double terminal() {
    double result = factor();
    while (siguienteCaracter() == '*' || siguienteCaracter() == '/') {
        char op = siguienteCaracter();
        esperaCaracter(op);
        if (op == '*') {
            result *= factor();
        } else {
            result /= factor();
        }
    }
    return result;
}

// Regla para la expresión
double expresion() {
    double result = terminal();
    while (siguienteCaracter() == '+' || siguienteCaracter() == '-') {
        char op = siguienteCaracter();
        esperaCaracter(op);
        if (op == '+') {
            result += terminal();
        } else {
            result -= terminal();
        }
    }
    //esperaCaracter(';');
    return result;
}

int main() {
    //cout << "Digite una operacion: ";
    getline(cin, input);

    try {
        double result = expresion();
        if (pos != input.size()) {
            throw runtime_error("Error inesperado, no se pudo completar el analisis");
        }
        cout << "" << result << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
