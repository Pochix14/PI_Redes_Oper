CXX := g++
CFLAGS := -g -c
DEPS := Mailbox.h
TARGETS := MailboxSend.out MailboxRcv.out

ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CFLAGS) $<

%.out: %.o Mailbox.o MsgSend.o MsgReceive.o
	$(info $$^ = $^)
	$(CXX) -g $^ Mailbox.o MsgSend.o MsgReceive.o -o $^

MailboxSend.out: Mailbox.o MsgSend.o
	$(CXX) -g Mailbox.o MsgSend.o -o $@

MailboxRcv.out: Mailbox.o MsgReceive.o 
	$(CXX) -g Mailbox.o MsgReceive.o  -o $@

clean:
	rm -f *.o *.out