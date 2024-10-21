
CC = cl.exe
CXX = cl.exe
CFLAGS = /I.. 
CXXFLAGS = $(CFLAGS)
RM = del

EXE_EXT = .exe
OBJ_EXT = .obj

all: tests

!include "rules.mk"


tests: $(TESTS)

.SUFFIXES: .obj.exe
.obj.exe:
	$(CXX) /o $@ $?

.SUFFIXES: .cpp.obj
.cpp.obj:
	$(CXX) /c $? $(CFLAGS)
clean:
	$(RM) $(TESTS) $(OBJS)
