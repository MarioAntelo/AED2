CXX		= g++
TARGETS = cadena.o

all: principal 

principal: main.cpp $(TARGETS)
	$(CXX) main.cpp $(TARGETS) -o principal

clean: 
	rm $(TARGETS) principal

.SUFFIXES: .cpp .h
	.o