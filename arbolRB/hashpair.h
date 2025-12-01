#ifndef HASHPAIR_H
#define HASHPAIR_H

#include <string>
#include <sstream>

template <typename V>
struct HashPair {
  std::string key;
  V value;

  HashPair(const std::string& k) : key(k), value(V()) {}
  HashPair(const std::string& k, const V& v) : key(k), value(v) {}

  std::string toString() const {
    std::stringstream ss;
    ss << "(" << key << " : " << value << ")";
    return ss.str();
  }
};

#endif
