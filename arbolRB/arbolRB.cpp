#include "arbolRB.h"

NodoRB::NodoRB(void* dato) : NodoSVG(dato){
  parent = NULL;
  rojo = true; // por defecto, al insertar, los nodos son rojos
}

void NodoRB::postConstructor(){
	NodoSVG::postConstructor();
	this->parent = NULL;
	this->rojo = true;
}

ArbolRB::ArbolRB(string T): ArbolSVG(T){
}

int ArbolRB::compareDatos(void* a, void* b){
	if( T == T(string) ){
		string* d1 = (string*)a;
		string* d2 = (string*)b;
		return d1->compare(*d2);
	}
	else if( T == T(int) ) {
		int* d1 = (int*)a;
		int* d2 = (int*)b;
		if (*d1 < *d2) return -1;
		else if (*d1 > *d2) return 1;
		else return 0;
	} else {
		//como ultimo compara direcciones de memoria
		if( a < b ) return -1;
		else if( a > b ) return 1;
		else return 0;
	}
}

void ArbolRB::leftRotate(NodoRB* x){
	if(x == NULL || x->der == NULL) return;
	NodoRB* y = (NodoRB*)x->der;
	x->der = y->izq;
	if(y->izq != NULL) ((NodoRB*)y->izq)->parent = x;
	y->parent = x->parent;
	if(x->parent == NULL){
		raiz = y;
	} else if(x == x->parent->izq){
		x->parent->izq = y;
	} else {
		x->parent->der = y;
	}
	y->izq = x;
	x->parent = y;
}

void ArbolRB::rightRotate(NodoRB* x){
	if(x == NULL || x->izq == NULL) return;
	NodoRB* y = (NodoRB*)x->izq;
	x->izq = y->der;
	if(y->der != NULL) ((NodoRB*)y->der)->parent = x;
	y->parent = x->parent;
	if(x->parent == NULL){
		raiz = y;
	} else if(x == x->parent->der){
		x->parent->der = y;
	} else {
		x->parent->izq = y;
	}
	y->der = x;
	x->parent = y;
}

void ArbolRB::insert(void* dato){
	NodoRB* z = new NodoRB(dato);
	z->T = T;
	z->postConstructor();

	NodoRB* y = NULL;
	NodoRB* x = (NodoRB*)raiz;

	// BST insert with parent tracking
	while(x != NULL){
		y = x;
		int cmp = compareDatos(dato, x->dato);
		if(cmp < 0) x = (NodoRB*)x->izq;
		else x = (NodoRB*)x->der;
	}
	z->parent = y;
	if(y == NULL){
		raiz = z;
	} else {
		int cmp = compareDatos(dato, y->dato);
		if(cmp < 0) y->izq = z;
		else y->der = z;
	}

	// Fixup para restaurar propiedades RB
	insertFixup(z);
}
void ArbolRB::insertFixup(NodoRB* z){
	// Mientras el padre exista y sea rojo
	while(z->parent != NULL && ((NodoRB*)z->parent)->rojo){
		NodoRB* p = (NodoRB*)z->parent;
		NodoRB* g = (NodoRB*)p->parent;
		if(g == NULL) break; // seguridad

		if(p == g->izq){
			NodoRB* y = (NodoRB*)g->der; // uncle
			bool yRojo = (y != NULL && y->rojo);
			if(yRojo){
				p->rojo = false;
				y->rojo = false;
				g->rojo = true;
				z = g;
			} else {
				if(z == p->der){
					z = p;
					leftRotate(z);
					p = (NodoRB*)z->parent; // actualizar p
					g = (NodoRB*)p->parent;
				}
				p->rojo = false;
				if(g){
					g->rojo = true;
					rightRotate(g);
				}
			}
		} else {
			NodoRB* y = (NodoRB*)g->izq; // uncle
			bool yRojo = (y != NULL && y->rojo);
			if(yRojo){
				p->rojo = false;
				y->rojo = false;
				g->rojo = true;
				z = g;
			} else {
				if(z == p->izq){
					z = p;
					rightRotate(z);
					p = (NodoRB*)z->parent;
					g = (NodoRB*)p->parent;
				}
				p->rojo = false;
				if(g){
					g->rojo = true;
					leftRotate(g);
				}
			}
		}
	}
	// Asegurar raiz negra
	if(raiz != NULL) ((NodoRB*)raiz)->rojo = false;
}

Nodo* ArbolRB::search(void* dato){
	NodoRB* it = (NodoRB*)raiz;
	while(it != NULL){
		int cmp = compareDatos(dato, it->dato);
		if(cmp == 0) return it;
		else if(cmp < 0) it = (NodoRB*)it->izq;
		else it = (NodoRB*)it->der;
	}
	return NULL;
}

string ArbolRB::toSVG(){
	NodoSVG* root = (NodoSVG*)raiz;
	// asignar coordenadas reutilizando ArbolSVG
	int xRef = 1;
	int horizontalSpacing = 50;
	int verticalSpacing = 80;
	asignarCoordenadas((NodoSVG*)root, 0, xRef, horizontalSpacing, verticalSpacing);

	// Calcular bounds del árbol para ajustar viewBox
	int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
	function<void(NodoSVG*)> computeBounds = [&](NodoSVG* n){
		if(n == NULL) return;
		if(n->x < minX) minX = n->x;
		if(n->x > maxX) maxX = n->x;
		if(n->y < minY) minY = n->y;
		if(n->y > maxY) maxY = n->y;
		computeBounds((NodoSVG*)n->izq);
		computeBounds((NodoSVG*)n->der);
	};
	computeBounds(root);
	if(minX == INT_MAX){ minX = 0; maxX = 200; minY = 0; maxY = 200; }
	int margin = 40;
	int vbMinX = minX - margin;
	int vbMinY = minY - margin; // include top margin so root is not cut
	int vbWidth = (maxX - minX) + margin*2;
	int vbHeight = (maxY - minY) + margin*2;

	stringstream svgContent;
	svgContent << "<svg viewBox=\""<<vbMinX<<" "<<vbMinY<<" "<<vbWidth<<" "<<vbHeight<<"\" xmlns=\"http://www.w3.org/2000/svg\" style=\"width: 100%; height: auto;\">";

	// Lambda simple que pinta con color segun NodoRB
	auto dibujarNodo = [&](const auto &self, NodoSVG* node, stringstream& svgContent) -> void {
		if(node == NULL) return;

		if(node->izq != NULL){
			svgContent << "<line x1=\""<<node->x<<"\" y1=\""<<node->y<<"\" x2=\""<<((NodoSVG*)node->izq)->x<<"\" y2=\""<<((NodoSVG*)node->izq)->y<<"\" stroke=\"black\"/>";
		}
		if(node->der != NULL){
			svgContent << "<line x1=\""<<node->x<<"\" y1=\""<<node->y<<"\" x2=\""<<((NodoSVG*)node->der)->x<<"\" y2=\""<<((NodoSVG*)node->der)->y<<"\" stroke=\"black\"/>";
		}

		NodoRB* nr = (NodoRB*)node;
		string fill = (nr->rojo ? "#d9534f" : "#222");
		string textColor = "white";
		int radius = 18;

		svgContent << "<circle cx=\""<<node->x<<"\" cy=\""<<node->y<<"\" r=\""<<radius<<"\" fill=\""<<fill<<"\" stroke=\"#333\" stroke-width=\"1\"/>";
		svgContent << "<text x=\""<<node->x<<"\" y=\""<<(node->y + 5)<<"\" text-anchor=\"middle\" font-size=\"12\" fill=\""<<textColor<<"\">"<<node->toString()<<"</text>";

		self(self, (NodoSVG*)node->izq, svgContent);
		self(self, (NodoSVG*)node->der, svgContent);
	};

	dibujarNodo(dibujarNodo, root, svgContent);
	svgContent << "</svg>";
	return svgContent.str();
}
