// Implementations for bstTree (moved from header)
#include "../include/bstTree.h"

Nodo::Nodo(void* dato){
	this->dato = dato;
	izq = NULL;
	der = NULL;
}

Nodo::~Nodo(){
	//no se hace delete del dato por que el arbol no es duenio del dato
}

string Nodo::toString(){
	stringstream ss;
	if(T == "int"){
		int* dato = (int*)this->dato;
		ss << *dato;
	}
	else if(T == "string"){
		string* dato = (string*)this->dato;
		ss << *dato;
  } else {
		ss << "{" << this->dato << "}";
	}
	return ss.str();
}

ostream& operator<<(ostream& os, Nodo*& node){
	os << node->toString();
	return os;
}

void Nodo::postConstructor(){
	// default does nothing
}

ArbolBST::ArbolBST(string T){
	raiz = NULL;
	this->T = T;
}
// Insertar por valor
template<typename U>
void insert(U valor) {
  U* copia = new U(valor);
  insert((void*)copia);
}

// Insertar por referencia
template<typename U>
void insert(U& valor) {
  U* copia = new U(valor);
  insert((void*)copia);
}

// Insertar puntero
template<typename U>
void insert(U* ptr) {
  insert((void*)ptr);
}

void ArbolBST::insert(void* dato){
	Nodo* nuevoNodo = new Nodo(dato);
	nuevoNodo->T = T;
	nuevoNodo->postConstructor(); // IMPORTANTE para que las clases derivadas se inicialicen !!

	if(raiz == NULL){
		raiz = nuevoNodo;
	}else{
		Nodo *it = raiz, *p = NULL;
		char donde = 'D';

		// buscar el campo
		while(it != NULL){
			p = it;
			if( T == T(string) ){
				string* d1 = (string*)dato;
				string* d2 = (string*)it->dato;
				if( d1->compare(*d2) < 0 ){
					it = it->izq; donde = 'I';
				}
				else{
					it = it->der; donde = 'D';
				}
			}
			else if( T == T(int) || T == T(float) || T == T(double) ){

				int* d1 = (int*)dato;
				int* d2 = (int*)it->dato;

				if( *d1 < *d2 ){
					it = it->izq; donde = 'I';
				}
				else{
					it = it->der; donde = 'D';
				}
			}
			else{
				if( dato < it->dato ){ // OJO...
					it = it->izq; donde = 'I';
				}
				else{
					it = it->der; donde = 'D';
				}
			}

		}// while

		// realizar la inserci�n
		if(donde == 'I') p->izq = nuevoNodo;
		else p->der = nuevoNodo;

	}//else

}

void ArbolBST::encolar(Nodo*& cola, Nodo*& dato){
	Nodo* nuevoNodo = new Nodo(dato);
	if(cola == NULL) cola = nuevoNodo;
	else{
		Nodo* it = cola;
		while(it->der != NULL) it = it->der;
		it->der = nuevoNodo;
	}
}

void ArbolBST::porNiveles(stringstream& ss){
	Nodo* cola = NULL;
	encolar(cola, raiz);
	while(cola != NULL){
		Nodo* sacarDeCola = cola;
		cola = cola->der;

		Nodo* nodoArbol = (Nodo*)sacarDeCola->dato;
		delete sacarDeCola;

		ss << datoToString(nodoArbol->dato) << ", "; // y aqui tambien en datoToString

		if(nodoArbol->izq != NULL) encolar(cola, nodoArbol->izq);
		if(nodoArbol->der != NULL) encolar(cola, nodoArbol->der);

	}
}


void ArbolBST::inorder(Nodo* n, stringstream& ss){
  if (n == NULL) return;

  if (n->izq != NULL)
    inorder(n->izq, ss);

  ss << datoToString(n->dato) << ", ";

  if (n->der != NULL)
    inorder(n->der, ss);
}

void ArbolBST::preorder(Nodo* n, stringstream& ss){
  if (n == NULL) return;

  ss << datoToString(n->dato) << ", ";

  if (n->izq != NULL)
    preorder(n->izq, ss);
  if (n->der != NULL)
    preorder(n->der, ss);
}

void ArbolBST::postorder(Nodo* n, stringstream& ss){
  if (n == NULL) return;

  if (n->izq != NULL)
    postorder(n->izq, ss);
  if (n->der != NULL)
    postorder(n->der, ss);

  ss << datoToString(n->dato) << ", ";
}


string ArbolBST::toString(){
  stringstream ss;

  if (raiz == NULL) {
    ss << "Niveles: (vacio)\n";
    ss << "Preorder: (vacio)\n";
    ss << "Inorder: (vacio)\n";
    ss << "Postorder: (vacio)\n";
    return ss.str();
  }

  ss << "Niveles: ";
  porNiveles(ss);
  ss << "\n";

  ss << "Preorder: ";
  preorder(raiz, ss);
  ss << "\n";

  ss << "Inorder: ";
  inorder(raiz, ss);
  ss << "\n";

  ss << "Postorder: ";
  postorder(raiz, ss);
  ss << "\n";

  return ss.str();
}




NodoSVG::NodoSVG(void* dato) : Nodo(dato){
	postConstructor();
}

void NodoSVG::postConstructor(){
	this->x = 0; // coordenada x
	this->y = 0; // coordenada y
}

ArbolSVG::ArbolSVG(string T) : ArbolBST(T) { }

void ArbolSVG::asignarCoordenadas(NodoSVG* node, int depth, int& xRef, int horizontalSpacing, int verticalSpacing){
	if(node == NULL) return;

	if(node->izq != NULL){
		asignarCoordenadas((NodoSVG*)node->izq, depth + 1, xRef, horizontalSpacing, verticalSpacing);
	}

	node->x = xRef * horizontalSpacing;
	node->y = depth * verticalSpacing;
	xRef += 1;

	if(node->der != NULL){
		asignarCoordenadas((NodoSVG*)node->der, depth + 1, xRef, horizontalSpacing, verticalSpacing);
	}
}

int ArbolSVG::getTreeSize(NodoSVG* node){
	if(node == NULL) return 0;
	return 1 + max(getTreeSize((NodoSVG*)node->izq), getTreeSize((NodoSVG*)node->der));
}

string ArbolSVG::toSVG(){
	NodoSVG* root = (NodoSVG*)raiz;
	int svgWidth = 800;
	int svgHeight = 600;
	int horizontalSpacing = 50; // espacio entre nodos en x
	int verticalSpacing = 80;   // espacio entre niveles en y

	int xRef = 1; // referencia para el x
	asignarCoordenadas(root, 0, xRef, horizontalSpacing, verticalSpacing);

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

	auto dibujarNodo = [&](const auto &self, NodoSVG* node, stringstream& svgContent) -> void {
		if(node == NULL) return;

		if(node->izq != NULL){
			svgContent << "<line x1=\""<<node->x<<"\" y1=\""<<node->y<<"\" x2=\""<<((NodoSVG*)node->izq)->x<<"\" y2=\""<<((NodoSVG*)node->izq)->y<<"\" stroke=\"black\"/>";
		}

		if(node->der != NULL){
			svgContent << "<line x1=\""<<node->x<<"\" y1=\""<<node->y<<"\" x2=\""<<((NodoSVG*)node->der)->x<<"\" y2=\""<<((NodoSVG*)node->der)->y<<"\" stroke=\"black\"/>";
		}

		int radius = 18;
		svgContent << "<circle cx=\""<<node->x<<"\" cy=\""<<node->y<<"\" r=\""<<radius<<"\" fill=\"lightblue\" stroke=\"#333\" stroke-width=\"1\"/>";
		svgContent << "<text x=\""<<node->x<<"\" y=\""<<(node->y + 5)<<"\" text-anchor=\"middle\" font-size=\"12\" fill=\"#111\">"<<node->toString()<<"</text>";

		self(self, (NodoSVG*)node->izq, svgContent);
		self(self, (NodoSVG*)node->der, svgContent);
	};

	dibujarNodo(dibujarNodo, root, svgContent);
	svgContent << "</svg>";

	return svgContent.str();
}

int ArbolSVG::toSVG(string outfilename){
	string filename = "../assets/svgTreeViewerTemplate.html";
	if(outfilename.compare(filename) == 0){
		cout << "No se puede sobrescribir el archivo" << filename << endl;
		return -1;
	}

	size_t fileLen = 0;
	struct stat fileStat;
	if( ( stat (filename.c_str(), &fileStat) ) == 0){
		fileLen = fileStat.st_size;
	}

	ifstream fileIn;
	fileIn.open(filename.c_str(), ios::in | ios::binary );
	if( !fileIn.is_open() ){
		cout << "No se pudo abrir el archivo" << filename << endl;
		return -1;
	}

	stringstream svgHTMLJS;
	svgHTMLJS.str(string());
	svgHTMLJS << fileIn.rdbuf();
	fileIn.close();

	string svgHTMLJS_str = svgHTMLJS.str();
	string svg = toSVG();

	string replacePattern = "%s";
	int replacePatternIndex = svgHTMLJS_str.find(replacePattern);
	if( replacePatternIndex == -1 ){
		cout << "No se pudo encontrar el patr�n de reemplazo." << endl;
		return -1;
	}

	ofstream fileOut;
	fileOut.open(outfilename.c_str(), ios::out | ios::binary );
	if( !fileOut.is_open() ){
		cout << "No se pudo abrir el archivo" << outfilename << endl;
		return -1;
	}
	fileOut << svgHTMLJS_str.substr(0, replacePatternIndex);
	fileOut << svg;
	fileOut << svgHTMLJS_str.substr( replacePatternIndex + replacePattern.length() );
	fileOut.close();

	cout << "Se gener� el visualizador '"<< outfilename <<"'.\nPor favor, proceda a abrilo desde un navegador web." << endl;

	// El archivo se generó; no abrir automáticamente según la política del proyecto.
	return 0;
}

string ArbolBST::datoToString(void* dato) {
    Nodo temp(dato);
    temp.T = T;
    return temp.toString();
}
