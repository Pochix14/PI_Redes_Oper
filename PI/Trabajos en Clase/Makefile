# Linux Makefile
# Socket class with SSL
#

CC  := gcc
CXX := g++
CFLAGS := -g -c
CXXFLAGS := -g -c 
LDFLAGS := -lssl -lcrypto
DEPS := Socket.h
TARGETS := mirrorServer.out mirrorClient.out

ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) $<

%.out: %.o Socket.o
	$(info $$^ = $^)
	$(CXX) $^ Socket.o $(LDFLAGS) -o $^

mirrorServer.out: ForkMirrorServerTest.o  Socket.o
	$(CXX) ForkMirrorServerTest.o Socket.o $(LDFLAGS) -o $@

mirrorClient.out: MirrorClientTest.o Socket.o
	$(CXX) MirrorClientTest.o Socket.o $(LDFLAGS) -o $@

clean:
	rm -f *.o *.out