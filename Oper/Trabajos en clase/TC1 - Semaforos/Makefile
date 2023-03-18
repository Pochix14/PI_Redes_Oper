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
DEPS := Sem.h
TARGETS := Sem.out

ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CFLAGS) $<

%.out: %.o Sem.o
	$(info $$^ = $^)
	$(CXX) -g $^ Sem.o -o $^

Sem.out: Sem.o
	$(CXX) -g Sem.o -o $@

clean:
	rm -f *.o *.out