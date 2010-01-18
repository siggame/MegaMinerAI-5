SRCS=$(shell ls *.cpp 2> /dev/null)
CXXOBJ_DEBUG=$(SRCS:.cpp=.od)
CXXOBJ_RELEASE=$(SRCS:.cpp=.o)
CSRCS=$(shell ls *.c 2> /dev/null)
COBJ_DEBUG=$(CSRCS:.c=.od)
COBJ_RELEASE=$(CSRCS:.c=.o)
CXX_FLAGS=-W -Wall
C_FLAGS=-W -Wall
LD_FLAGS=-W -Wall
CXX=g++
CC=gcc
LD=g++
RM=rm -f

OBJ_DEBUG=$(shell ls *.od | grep -v main.od| 2> /dev/null)
OBJ_RELEASE=$(shell ls *.o | grep -v main.o| 2> /dev/null)
default: debug

all: debug release

debug: main_debug

release: main

clean:
	$(RM) *.od *.o main main_debug

extra_clean: clean
	rm -f *~

%.od: %.cpp
	$(CXX) -g $(CXX_FLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) -O3 $(CXX_FLAGS) -c -o $@ $<

%.od: %.c
	$(CC) -g $(C_FLAGS) -c -o $@ $<

%.o: %.c
	$(CC) -O3 $(C_FLAGS) -c -o $@ $<

main_debug: $(CXXOBJ_DEBUG) $(COBJ_DEBUG)
	$(LD) -g  $(LD_FLAGS) $(OBJ_DEBUG) -o $@ $(CXXOBJ_DEBUG) $(COBJ_DEBUG) 
	
main: $(CXXOBJ_RELEASE) $(COBJ_RELEASE) 
	$(LD) -O3 $(LD_FLAGS) $(OBJ_RELEASE) -o $@ $(CXXOBJ_RELEASE) $(COBJ_RELEASE)
