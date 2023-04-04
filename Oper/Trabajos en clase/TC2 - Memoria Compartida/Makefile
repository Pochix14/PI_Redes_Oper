# EXE= Sem
# CXX= g++
# FLAGS= -g -c
# DEPS= Sem.h

# all: $(EXE)

# $(EXE): $(DEPS)
# 	$(CXX) $(FLAGS) -o $(EXE)

# .PHONY: lint
# lint:
# 	cpplint --filter=-readability/casting Sem.cc

# .PHONY: clean
# clean:
# 	rm -f *.o *.out

CXX := g++
CFLAGS := -g -c
DEPS := Sem.h ShrMemory.h
TARGETS := Test.out

ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CFLAGS) $<

%.out: %.o Sem.o ShrMemory.o Test.o
	$(info $$^ = $^)
	$(CXX) -g $^ Sem.o ShrMemory.o Test.o -o $^

Test.out: Sem.o ShrMemory.o Test.o
	$(CXX) -g Sem.o ShrMemory.o Test.o -o $@

clean:
	rm -f *.o *.out