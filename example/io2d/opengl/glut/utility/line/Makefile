GXX = g++-7
CXXFLAGS += -std=c++1z -O3 -Wall -Wextra -pedantic -I /usr/local/include -framework GLUT -framework OpenGL -pthread
#LDFLAGS += -lglut

all: gsline

gsline:
	$(GXX) $(CXXFLAGS) gsline.cpp

run:
	./a.out

clean:
	$(RM) a.out
