OPT ?= -g2

CFLAGS += -I./net $(OPT)
CXXFLAGS += -I./net $(OPT)

NET_SOURCES = $(shell find net -name '*.cc')
NET_OBJ = $(NET_SOURCES:.cc=.o)

TEST_SOURCES = $(shell find net_test -name '*.cc')
TEST_OBJ = $(TEST_SOURCES:.cc=.o)

all: daemon

daemon :$(TEST_OBJ) $(NET_OBJ)
	$(CXX) $^ -o $@

.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

