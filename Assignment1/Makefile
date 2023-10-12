CXX = g++
CXXFLAGS = -Wall -pedantic -O3
INCLUDE_DIRS = -I./stb_image -I./commands -I./image -I./inverse
OUTPUT = intensityTransform

all: main.o command.o myImage.o inverse.o identity.o log.o inverseLog.o nthPower.o colorPieceWise.o
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $^ -o $(OUTPUT)
	./$(OUTPUT)


main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

command.o: commands/command.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

myImage.o: image/myImage.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

inverse.o: inverse/inverse.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

identity.o: identity/identity.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

log.o: log/log.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

inverseLog.o: inverseLog/inverseLog.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

nthPower.o: nthPower/nthPower.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

colorPieceWise.o: colorPieceWise/colorPieceWise.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

clean:
	rm -f $(OUTPUT) *.o
