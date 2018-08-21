CXX=g++
CC=gcc
C_FLAGS+=-g -std=c++11

TEST_TARGETS = TestCoContextSys TestCoContextRuntime TestCoContextUtil TestTimer TestEpollClient TestEpollServer
SRCS=CoContext.cc CoContextSys.cc CoContextRuntime.cc CoContextUtil.cc Timer.cc CoContextEpoll.cc 
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

TestCoContextUtil : TestCoContextUtil.cc
	@echo "Compiling $^ ==> $@..."
	$(CXX) $^ $(OBJS) -o $@ $(C_FLAGS)

TestTimer : TestTimer.cc
	@echo "Compiling $^ ==> $@..."
	$(CXX) $^ $(OBJS) -o $@ $(C_FLAGS)

TestEpollClient: TestEpollClient.cc
	@echo "Compiling $^ ==> $@..."
	$(CXX) $^ $(OBJS) -o $@ $(C_FLAGS)

TestEpollServer: TestEpollServer.cc
	@echo "Compiling $^ ==> $@..."
	$(CXX) $^ $(OBJS) -o $@ $(C_FLAGS)

clean:
	@ rm -rf *.o
	@ rm -rf $(TEST_TARGETS)

