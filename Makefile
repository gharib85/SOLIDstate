CC=g++
CFLAGS= -O3 -std=c++17
LIBS= -larmadillo

src=$(wildcard Modules/*/*.cpp\
      wildcard Modules/*.cpp\
	  main.cpp)
obj=$(src:.cpp=.o)

%.o: %.cpp %.hpp
	$(CC) -o $@ -c $< -std=c++17

main.o: main.cpp $(obj)
	$(CC) -o main.exe $^ $(LIBS) $(CFLAGS)

.PHONY : clean
clean:
	rm -f $(obj) main.exe