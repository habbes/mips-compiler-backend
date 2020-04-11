CXX = g++
SRC := $(wildcard ./*.cpp)
OBJ := $(SRC:.cpp=.o)

ALL_SRC := $(wildcard ./*.cpp)

MAIN_SRC := $(subst ./test.cpp,,${ALL_SRC})
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

TEST_SRC := $(subst ./main.cpp,,${ALL_SRC})
TEST_OBJ = $(TEST_SRC:.cpp=.o)

LDFLAGS =
CXXFLAGS = -std=c++17 -g -Wall

main: $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -fsanitize=address

test: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -fsanitize=address

.PHONY: clean
clean:
	rm -rf $(OBJ) test test_mem main