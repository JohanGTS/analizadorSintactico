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

    if (siguienteCaracter()=='-')
    {
        esperaCaracter('-');
        return -factor();
    }else if (isdigit(siguienteCaracter())) {
        return encuentraNumero();
    } else if (siguienteCaracter() == '(') {
        esperaCaracter('(');
        double resultado = expresion();
        esperaCaracter(')');
        return resultado;
    }  else {
        throw runtime_error("Error se esperaba un numero o '(' en la posicion " + to_string(pos));
    }
}

// Multiplicacion y division
double terminal() {
    double resultado = factor();
    while (siguienteCaracter() == '*' || siguienteCaracter() == '/') {
        char op = siguienteCaracter();
        esperaCaracter(op);
        if (op == '*') {
            resultado *= factor();
        } else {
            resultado /= factor();
        }
    }
    return resultado;
}

// Regla para la expresión
double expresion() {
    double resultado = terminal();
    while (siguienteCaracter() == '+' || siguienteCaracter() == '-') {
        char op = siguienteCaracter();
        esperaCaracter(op);
        if (op == '+') {
            resultado += terminal();
        } else {
            resultado -= terminal();
        }
    }
    return resultado;
}

int main() {
    getline(cin, input);

    try {
        double resultado = expresion();
        esperaCaracter(';');

        if (pos != input.size()) {
            throw runtime_error("Error inesperado, no se pudo completar el analisis");
        }
        cout << resultado << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
