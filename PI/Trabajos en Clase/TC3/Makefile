

# Linux Makefile
# Socket class with SSL
#

CC  := gcc
CXX := g++
CFLAGS := -g -c
CXXFLAGS := -g -c 
LDFLAGS := -lssl -lcrypto
DEPS := Socket.h
TARGETS := ipv4-ssl-cli.out ipv6-ssl-cli.out

ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) $<

%.out: %.o Socket.o
	$(info $$^ = $^)
	$(CXX) $^ Socket.o $(LDFLAGS) -o $^

ipv4-ssl-cli.out: ipv4-ssl-cli.o Socket.o
	$(CXX) ipv4-ssl-cli.o Socket.o $(LDFLAGS) -o $@

ipv6-ssl-cli.out: ipv6-ssl-cli.o Socket.o
	$(CXX) ipv6-ssl-cli.o Socket.o $(LDFLAGS) -o $@

clean:
	rm -f *.o *.out
