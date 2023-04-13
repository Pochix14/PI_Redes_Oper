CXX := g++
CFLAGS := -g -c
DEPS := ShrMemory.h HotPotato.h IOManager.h main.cc
TARGETS := potato.out

ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CFLAGS) $<

%.out: %.o ShrMemory.o HotPotato.o IOManager.o main.o
	$(info $$^ = $^)
	$(CXX) -g $^ ShrMemory.o HotPotato.o IOManager.o main.o -o $^

potato.out: ShrMemory.o HotPotato.o IOManager.o main.o
	$(CXX) -g ShrMemory.o HotPotato.o IOManager.o main.o -o $@

clean:
	rm -f *.o *.out