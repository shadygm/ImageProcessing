CXX = g++
CXXFLAGS = -Wall -pedantic -g -O3
INCLUDE_DIRS = -I./stb_image -I./commands -I./images
OUTPUT = filter

all: main.o command.o myImage.o lowPass.o rmSaltPepper.o imageSharpening.o 
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $^ -o $(OUTPUT)
	./$(OUTPUT)


main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

command.o: commands/command.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

myImage.o: images/myImage.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

lowPass.o : lowPassFilter/lowPass.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

rmSaltPepper.o : rmSaltPepper/rmSaltPepper.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

imageSharpening.o : imageSharpening/imageSharpening.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

clean: 
	rm -f $(OUTPUT) *.o
