CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = arbolRB/svgTreViewer.cpp \
      arbolRB/arbolRB.cpp \
      arbolRB/bstTree.cpp

OUT = programa

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

run: all
	./$(OUT)

clean:
	rm -f $(OUT) *_svgTreeViewer.html

