GXX = g++-7
CXXFLAGS += -std=c++1z -O3 -Wall -Wextra -pedantic -I /usr/local/include -framework GLUT -framework OpenGL -pthread
#LDFLAGS += -lglut

all: gsline

gsline:
	$(GXX) $(CXXFLAGS) ./straight.cpp -o straight
	$(GXX) $(CXXFLAGS) ./hermite.cpp -o hermite

run:
	./straight
	./hermite

clean:
	$(RM) straight hermite
