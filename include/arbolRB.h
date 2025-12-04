#ifndef ARBOLRB_H
#define ARBOLRB_H

#include "bstTree.h"
#include <functional>
#include <climits>

using namespace std;

// node of Red-Black Tree
class NodoRB : public NodoSVG {
  public:
  bool rojo; // true = red, false = black
  NodoRB* parent;

  NodoRB(void* dato);
  void postConstructor();
};


class ArbolRB : public ArbolSVG {
  public:
  ArbolRB(string T);
  using ArbolSVG::toSVG; // expose base class overloads (toSVG(string))

  virtual int compareDatos(void* a, void* b);

  void leftRotate(NodoRB* x);
  void rightRotate(NodoRB* x);

  void insert(void* dato);
  void insertFixup(NodoRB* z);

  void deleteDato(void* dato);
  void deleteFixup(NodoRB* x, NodoRB* parentDeX);

  NodoRB* minimum(NodoRB* n);

  Nodo* search(void* dato);

  // Override toSVG to color nodes according to their color
  string toSVG();
  // Convert data to string (e.g., Persona)
  virtual string datoToString(void* dato) override;
};

#endif // ARBOLRB_H