OPT ?= -g2

CFLAGS += -I./net $(OPT)
CXXFLAGS += -I./net $(OPT) -std=c++11

NET_SOURCES = $(shell find net -name '*.cc')
NET_OBJ = $(NET_SOURCES:.cc=.o)

TEST_SOURCES = $(shell find net_test -name '*.cc')
TEST_OBJ = $(TEST_SOURCES:.cc=.o)

all: daemon clean

daemon :$(TEST_OBJ) $(NET_OBJ)
	$(CXX) $^ -o $@

# 隐含规则包括了下面这个，但是写出来是最好的
# 定义模式规则
# .cc.o:
%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(TEST_OBJ) $(NET_OBJ)
