CXX=g++
CC=gcc
C_FLAGS+=-g -std=c++11

TEST_TARGETS = TestCoContextSys TestCoContextRuntime TestCoUtil
SRCS=CoContext.cc CoContextSys.cc CoContextRuntime.cc CoUtil.cc CoContextEpoll.cc Timer.cc
OBJS=$(patsubst %.cc, %.o, $(SRCS))

all : $(OBJS) $(TEST_TARGETS) 

$(OBJS):%.o:%.cc
	@echo "Compiling $^ ==> $@..."
	$(CXX) -c $^ -o $@ $(C_FLAGS)

TestCoContextSys : TestCoContextSys.cc
	@echo "Compiling $^ ==> $@..."
	$(CXX) $^ $(OBJS) -o $@ $(C_FLAGS)

TestCoContextRuntime : TestCoContextRuntime.cc
	@echo "Compiling $^ ==> $@..."
	$(CXX) $^ $(OBJS) -o $@ $(C_FLAGS)

TestCoUtil : TestCoUtil.cc
	@echo "Compiling $^ ==> $@..."
	$(CXX) $^ $(OBJS) -o $@ $(C_FLAGS)

clean:
	@ rm -rf *.o
	@ rm -rf $(TEST_TARGETS)

