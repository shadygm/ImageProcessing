CXX = g++
CXXFLAGS = -Wall -pedantic -O3
INCLUDE_DIRS = -I./stb_image -I./commands -I./images
OUTPUT = histogram

all: main.o command.o myImage.o histogram.o
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $^ -o $(OUTPUT)
	./$(OUTPUT)


main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

command.o: commands/command.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

myImage.o: images/myImage.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

histogram.o: histogramApply/histogram.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

clean:
	rm -f $(OUTPUT) *.o
