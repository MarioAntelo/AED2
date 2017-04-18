CXX		= g++
TARGETS = cadena.o func.o generador.o

all: principal experimento

principal: main.cpp $(TARGETS)
	$(CXX) main.cpp $(TARGETS) -o principal

experimento: experimento.cpp $(TARGETS)
	$(CXX) experimento.cpp $(TARGETS) -o experimento

clean: 
	rm $(TARGETS) principal experimento


.SUFFIXES: .cpp .h
	.o
