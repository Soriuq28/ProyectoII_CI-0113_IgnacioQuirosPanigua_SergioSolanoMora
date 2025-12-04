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
  // if age is equal, compare id; a smaller id means the person is older
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
  // to print Persona details
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
