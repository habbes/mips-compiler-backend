CXX = clang++
SRC := $(wildcard ./*.cpp)
OBJ := $(SRC:.cpp=.o)

LDFLAGS =
CXXFLAGS = -std=c++17 -g -Wall

test: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -fsanitize=address

test_mem: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -fsanitize=address


.PHONY: clean
clean:
	rm -rf $(OBJ) test