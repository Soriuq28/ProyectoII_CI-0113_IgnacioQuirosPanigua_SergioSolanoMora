#ifndef BSTTREE_H
#define BSTTREE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <functional>
#include <climits>
#include <algorithm>
#include <string>

using namespace std;

#define T(t) #t

class Nodo{
  public:
  void* dato;
  Nodo *izq, *der;
  string T;

  Nodo(void* dato);
  virtual ~Nodo();
  string toString();
  friend ostream& operator<<(ostream& os, Nodo*& node);
  virtual void postConstructor();
};

class ArbolBST{
  public:
  Nodo* raiz;
  string T;

  ArbolBST(string T);
  void insert(void* dato);
  void encolar(Nodo*& cola, Nodo*& dato);
  void porNiveles(stringstream& ss);
  void inorder(Nodo* n, stringstream& ss);
  void preorder(Nodo* n, stringstream& ss);
  void postorder(Nodo* n, stringstream& ss);
  string toString();
  virtual string datoToString(void* dato);
};


class NodoSVG : public Nodo {
  public:
  int x, y;
  NodoSVG(void* dato);
  void postConstructor();
};

class ArbolSVG : public ArbolBST {
  public:

  ArbolSVG(string T);
  void asignarCoordenadas(NodoSVG* node, int depth, int& xRef, int horizontalSpacing, int verticalSpacing);
  int getTreeSize(NodoSVG* node);
  virtual string toSVG();
  int toSVG(string outfilename);
};

#endif // BSTTREE_H