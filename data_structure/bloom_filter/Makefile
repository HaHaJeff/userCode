OPT ?= -g2 OPT

CFLAGS += -I./ $(OPT)
CXXFLAGS += -I./ $(OPT) -std=c++11
OPT = -D OPT


NET_SOURCES = $(shell find ./ -name '*.cc')
NET_OBJ = $(NET_SOURCES:.cc=.o)

all: test clean

#daemon :$(TEST_OBJ) $(NET_OBJ)
#	$(CXX) $^ -o $@

test: $(NET_OBJ)
	$(CXX) $^ -o $@ ${CMPOPT}
# 隐含规则包括了下面这个，但是写出来是最好的
# 定义模式规则
# .cc.o:
%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ ${CMPOPT}

.PHONY: clean
clean:
	rm $(TEST_OBJ) $(NET_OBJ)
