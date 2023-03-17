# Linux Makefile
# Socket class
#

CC  := gcc
CXX := g++
CFLAGS := -g -c
CXXFLAGS := -g -c
DEPS := Socket.h
TARGETS := ipv4-udp-client.out ipv4-udp-server.out

ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) $<

%.out: %.o Socket.o
	$(info $$^ = $^)
	$(CXX) -g $^ Socket.o -o $^

ipv4-udp-client.out: ipv4-udp-client.o Socket.o
	$(CXX) -g ipv4-udp-client.o Socket.o -o $@

ipv4-udp-server.out: ipv4-udp-server.o Socket.o
	$(CXX) -g ipv4-udp-server.o Socket.o -o $@

clean:
	rm -f *.o *.out