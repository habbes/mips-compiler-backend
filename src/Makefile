SRC := $(wildcard ./*.cpp)
OBJ := $(SRC:.cpp=.o)

LDFLAGS =
CXXFLAGS = -std=c++17 -g

test: $(OBJ)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJ) test