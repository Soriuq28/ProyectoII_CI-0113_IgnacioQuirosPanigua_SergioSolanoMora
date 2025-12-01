#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
using namespace std;

class Persona {
public:
  string nombre;
  int edad;
  double id;
  Persona() : nombre(""), edad(0), id(0) {}
  Persona(string n, int e, double i) : nombre(n), edad(e), id(i) {}
  // si edad es igual compara id, un id menor equivale a que la persona es mayor
  bool operator<(const Persona& other) const {
    if (edad != other.edad)
      return edad < other.edad;  
    return id > other.id;          
  }
  bool operator>(const Persona& other) const {
    if (edad != other.edad)
      return edad > other.edad;
    return id < other.id;          
  }
  // Para imprimir bonito
  friend ostream& operator<<(ostream& os, const Persona& p) {
      os << p.nombre << " (Edad: " << p.edad << ", ID: " << p.id << ")";
      return os;
  }
  string toString() const {
    stringstream ss;
    ss << nombre << " (" << edad << " años, id=" << id << ")";
    return ss.str();
  }
};

#endif
