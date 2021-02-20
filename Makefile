CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb -Wall -Wextra

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := lib

EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ -L$(LIBRARIES) -Wl,-rpath=$(LIBRARIES) -lUtil -lncurses

clean:
	-rm $(BIN)/*
