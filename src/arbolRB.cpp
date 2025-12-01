#include "../include/arbolRB.h"
#include "../include/persona.h"

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

	} else if ( T == "Persona" ) {
		Persona* p1 = (Persona*)a;
		Persona* p2 = (Persona*)b;
		if (*p1 < *p2) return -1;
		if (*p1 > *p2) return 1;
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

NodoRB* ArbolRB::minimum(NodoRB* n) {
    while (n->izq != NULL)
        n = (NodoRB*)n->izq;
    return n;
}

void ArbolRB::deleteDato(void* dato) {
    NodoRB* z = (NodoRB*)search(dato);
    if (z == NULL) return;

    NodoRB *y = z;
    NodoRB *x = NULL;
    bool yOriginalRojo = y->rojo;

    // Caso 1: no tiene hijo izquierdo
    if (z->izq == NULL) {
        x = (NodoRB*)z->der;
        NodoRB* parent = (NodoRB*)z->parent;

        if (z->parent == NULL) raiz = z->der;
        else if (z == z->parent->izq) z->parent->izq = z->der;
        else z->parent->der = z->der;

        if (z->der != NULL) ((NodoRB*)z->der)->parent = parent;

    }
    // Caso 2: no tiene hijo derecho
    else if (z->der == NULL) {
        x = (NodoRB*)z->izq;
        NodoRB* parent = (NodoRB*)z->parent;

        if (z->parent == NULL) raiz = z->izq;
        else if (z == z->parent->izq) z->parent->izq = z->izq;
        else z->parent->der = z->izq;

        if (z->izq != NULL) ((NodoRB*)z->izq)->parent = parent;

    }
    // Caso 3: tiene dos hijos
    else {
        y = minimum((NodoRB*)z->der);
        yOriginalRojo = y->rojo;
        x = (NodoRB*)y->der;

        NodoRB* yp = (NodoRB*)y->parent;

        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            if (y->parent->izq == y)
                y->parent->izq = y->der;
            else
                y->parent->der = y->der;

            if (y->der)
                ((NodoRB*)y->der)->parent = yp;

            y->der = z->der;
            ((NodoRB*)y->der)->parent = y;
        }

        if (z->parent == NULL)
            raiz = y;
        else if (z == z->parent->izq)
            z->parent->izq = y;
        else
            z->parent->der = y;

        y->parent = z->parent;
        y->izq = z->izq;
        ((NodoRB*)y->izq)->parent = y;
        y->rojo = z->rojo;
    }

    // Eliminar físicamente z
    delete z;

    // Si el nodo eliminado era negro, arreglar violaciones RB
    if (!yOriginalRojo)
        deleteFixup(x, (x ? x->parent : NULL));
}

void ArbolRB::deleteFixup(NodoRB* x, NodoRB* parent) {
    while ((x != raiz) && (x == NULL || !x->rojo)) {

        if (x == (parent ? parent->izq : NULL)) {
            NodoRB* w = (NodoRB*)(parent->der);

            if (w && w->rojo) {
                w->rojo = false;
                parent->rojo = true;
                leftRotate(parent);
                w = (NodoRB*)parent->der;
            }

            if ((w->izq == NULL || !((NodoRB*)w->izq)->rojo) &&
                (w->der == NULL || !((NodoRB*)w->der)->rojo)) {

                w->rojo = true;
                x = parent;
                parent = (NodoRB*)parent->parent;
            } else {
                if (w->der == NULL || !((NodoRB*)w->der)->rojo) {
                    if (w->izq) ((NodoRB*)w->izq)->rojo = false;
                    w->rojo = true;
                    rightRotate(w);
                    w = (NodoRB*)parent->der;
                }

                w->rojo = parent->rojo;
                parent->rojo = false;
                if (w->der) ((NodoRB*)w->der)->rojo = false;
                leftRotate(parent);
                x = (NodoRB*)raiz;
                break;
            }

        } else {
            // simétrico al anterior, pero usando lados opuestos
            NodoRB* w = (NodoRB*)(parent->izq);

            if (w && w->rojo) {
                w->rojo = false;
                parent->rojo = true;
                rightRotate(parent);
                w = (NodoRB*)parent->izq;
            }

            if ((w->der == NULL || !((NodoRB*)w->der)->rojo) &&
                (w->izq == NULL || !((NodoRB*)w->izq)->rojo)) {

                w->rojo = true;
                x = parent;
                parent = (NodoRB*)parent->parent;

            } else {
                if (w->izq == NULL || !((NodoRB*)w->izq)->rojo) {
                    if (w->der) ((NodoRB*)w->der)->rojo = false;
                    w->rojo = true;
                    leftRotate(w);
                    w = (NodoRB*)parent->izq;
                }

                w->rojo = parent->rojo;
                parent->rojo = false;
                if (w->izq) ((NodoRB*)w->izq)->rojo = false;
                rightRotate(parent);
                x = (NodoRB*)raiz;
                break;
            }
        }
    }

    if (x) x->rojo = false;
}


