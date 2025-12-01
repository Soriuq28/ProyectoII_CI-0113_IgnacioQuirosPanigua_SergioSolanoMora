#ifndef RBHASH_H
#define RBHASH_H

#include <string>
#include <sstream>
#include "arbolRB.h"
#include "hashpair.h"


using namespace std;

template <typename V>
class RBHash {
  struct HashPair {
  string key;
  V value;

  HashPair(const string& k) : key(k), value(V()) {}
  HashPair(const string& k, const V& v) : key(k), value(v) {}

  string toString() const {
    stringstream ss;
    ss << "(" << key << " : " << value << ")";
    return ss.str();
  }
};

  class RBHashTree : public ArbolRB {
    public:
    RBHashTree() : ArbolRB("hashpair") {}

    int compareDatos(void* a, void* b) override {
      HashPair* p1 = (HashPair*)a;
      HashPair* p2 = (HashPair*)b;
      return p1->key.compare(p2->key);
    }
    string datoToString(void* dato) override {
      HashPair* p = (HashPair*)dato;
      return p->toString();
    }

  };

  RBHashTree tree;

  public:
  RBHash() : tree() {
  }

  V& operator[](const string& key) {
    HashPair temp(key);
    Nodo* n = tree.search(&temp);

    if (n != NULL) {
      HashPair* p = (HashPair*)n->dato;
      return p->value;
    }

    HashPair* nuevo = new HashPair(key);
    tree.insert((void*)nuevo);
    return nuevo->value;
  }

  bool contains(const string& key) {
    HashPair temp(key);
    return tree.search(&temp) != NULL;
  }

  string toString() {
    return tree.toString();
  }

};

template <typename V>
ostream& operator<<(ostream& os, RBHash<V>& h) {
  os << h.toString();
  return os;
}

#endif // RBHASH_H
