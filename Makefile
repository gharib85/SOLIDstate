CC=g++
CFLAGS= -O3 -std=c++17
LIBS= -larmadillo

src=$(wildcard Modules/*/*/*.cpp\
	  wildcard Modules/*/*.cpp\
      wildcard Modules/*.cpp\
	  )
obj=$(src:.cpp=.o)

%.o: %.cpp %.hpp
	$(CC) -o $@ -c $< -std=c++17

# template initialization files pattern
%-imp.o: %-imp.cpp %.hpp %.cpp
	$(CC) -o $@ -c $< -std=c++17

main.exe: main.cpp $(obj)
	$(CC) -o main.exe $^ $(LIBS) $(CFLAGS)

solid: $(obj)
	ar rcs SOLIDstate.a $(obj)

solid.exe: main.cpp SOLIDstate.a 
	$(CC) -o solid.exe main.cpp SOLIDstate.a $(LIBS) $(CFLAGS)

doxy:
	doxygen Doxyfile
	firefox Doxy/html/index.html &

	# TODO make solution to this
	@echo "########################################"
	@echo "[!] REMEMBER modify INPUT in Doxyfile"
	@echo "########################################"

.PHONY : clean
clean:
	rm -f $(obj) main.exe