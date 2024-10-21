
CC ?= gcc
CXX ?= g++
#CFLAGS = -I.. -Wall -DDEBUG -O1 -fno-loop-optimize -fno-guess-branch-probability -fno-defer-pop -fno-merge-constants -fno-thread-jumps  -fno-delayed-branch -fno-if-conversion -fno-if-conversion2 -fno-omit-frame-pointer -fcprop-registers -fno-crossjumping
CFLAGS := -I.. -Wall -DDEBUG -O2 $(CFLAGS_ADD)
CXXFLAGS := $(CFLAGS) $(CXXFLAGS_ADD)

LDFLAGS = -L../build -lseh

EXE_EXT = .exe
OBJ_EXT = .o

all: tests

include rules.mk


.PHONY: tests
tests: $(TESTS)

%.exe: %.o
	$(CXX) -o $@ $? $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) $(TESTS) $(OBJS)
