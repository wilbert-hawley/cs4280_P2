FINAL = frontEnd
CXX = g++
CXXFLAGS = -Wall
MAIN_CPP = main.cpp
OBJS = main.o scanner.o testscanner.o fileOp.o parser.o
DEPS = scanner.h testscanner.h token.h fileOp.h parser.h

%.o: %.c $(MAIN_CPP) $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(FINAL): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	/bin/rm -f $(FINAL) *.o *.txt output.sp2022