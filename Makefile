FINAL = frontEnd
CXX = g++
CXXFLAGS = -Wall
MAIN_CPP = main.cpp
OBJS = main.o scanner.o fileOp.o parser.o node.o
DEPS = scanner.h token.h fileOp.h parser.h node.h

%.o: %.c $(MAIN_CPP) $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(FINAL): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	/bin/rm -f $(FINAL) *.o *.txt output.sp2022