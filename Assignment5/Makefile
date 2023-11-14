CXX = g++
CXXFLAGS = -Wall -pedantic -g -O3
INCLUDE_DIRS = -I./stb_image -I./commands -I./images
OUTPUT = topHat

all: main.o command.o myImage.o dilationErosion.o tophat.o
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $^ -o $(OUTPUT)
	./$(OUTPUT)


main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

command.o: commands/command.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

myImage.o: images/myImage.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

dilationErosion.o : dilationErosion/dilationErosion.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

tophat.o : tophat/tophat.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

clean: 
	rm -f $(OUTPUT) *.o
