CXX=g++
CXXFLAGS+= -g -std=c++11 -O2

SRCS=$(wildcard *.cc)
OBJS=$(patsubst %.cc, %.o, $(filter-out $(TEST),$(SRCS)))
TEST=TestUtil.cc TestDaemon.cc TestProcessInfo.cc TestStatus.cc TestTime.cc

all: $(OBJS) TestUtil TestDaemon TestProcessInfo TestStatus TestTime clean

TestUtil: TestUtil.cc $(OBJS)
	@echo "OBJS:" $(OBJS)
	@echo $^ "===>" $@
	$(CXX) $^ $(CXXFLAGS) -o $@

TestDaemon: TestDaemon.cc $(OBJS)
	@echo $^ "===>" $@
	$(CXX) $^ $(CXXFLAGS) -o $@

TestProcessInfo: TestProcessInfo.cc $(OBJS)
	@echo $^ "===>" $@
	$(CXX) $^ $(CXXFLAGS) -o $@

TestStatus: TestStatus.cc $(OBJS)
	@echo $^ "===>" $@
	$(CXX) $^ $(CXXFLAGS) -o $@

TestTime: TestTime.cc $(OBJS)
	@echo $^ "===>" $@
	$(CXX) $^ $(CXXFLAGS) -o $@

$(OBJS):%.o:%.cc
	@echo $^ "===>" $@
	$(CXX) -c $^ $(CXXFLAGS) -o $@

# when clean is a file in this directory, make clean will invalid if .PHONY not be declared
.PHONY:clean

clean:
	@rm *.o
