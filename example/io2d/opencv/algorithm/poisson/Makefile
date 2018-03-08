CXX ?= g++-7

CXXFLAGS += -std=c++1z -c -O3 -Wall -Wextra -pedantic -I /usr/local/include $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)

all: example

example: example.o; $(CXX) $< -o $@ $(LDFLAGS)

%.o: %.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: $(RM) example.o
