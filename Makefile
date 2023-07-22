versaoPythonLista = $(subst ., ,$(filter-out Python , $(shell python3 --version)))

ifneq ($(word 2, $(versaoPythonLista)),)

versaoPython = $(word 1, $(versaoPythonLista)).$(word 2, $(versaoPythonLista))

else

versaoPython = $(word 1, $(versaoPythonLista))

endif

CXX = g++
INCLUDEDIR1 = include/
INCLUDEDIR2 = /usr/include/python$(versaoPython)
FLAGS = -I $(INCLUDEDIR1) -I $(INCLUDEDIR2) $(NUM_THREADS2) $(TAMANHO_AMOSTRA2) -std=c++2a -lpython$(versaoPython) -lpthread -w

all: compilacao clean

compilacao: main.cpp
	$(CXX) main.cpp -o estimador-mm1 $(FLAGS)

clean:
	rm -f *.o
