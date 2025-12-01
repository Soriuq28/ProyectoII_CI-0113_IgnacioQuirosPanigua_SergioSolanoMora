#ifndef ARBOLRB_H
#define ARBOLRB_H

#include "bstTree.h"
#include <functional>
#include <climits>

using namespace std;

// Nodo para Arbol RB (hereda de NodoSVG para compatibilidad con SVG)
class NodoRB : public NodoSVG {
  public:
  bool rojo; // true = rojo, false = negro
  NodoRB* parent;

  NodoRB(void* dato);
  void postConstructor();
};


class ArbolRB : public ArbolSVG {
  public:
  ArbolRB(string T);
  using ArbolSVG::toSVG; // exponer las sobrecargas de la clase base (toSVG(string))

  virtual int compareDatos(void* a, void* b);

  void leftRotate(NodoRB* x);
  void rightRotate(NodoRB* x);

  void insert(void* dato);
  void insertFixup(NodoRB* z);

  void deleteDato(void* dato);
  void deleteFixup(NodoRB* x, NodoRB* parentDeX);
  
  NodoRB* minimum(NodoRB* n);

  Nodo* search(void* dato);

  // Sobrescribir toSVG para colorear nodos según su color
  string toSVG();
};

#endif // ARBOLRB_H