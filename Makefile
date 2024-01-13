CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = `pkg-config --cflags --libs opencv4`

SRC_FILES = main.cpp camera_capture.cpp file_operations.cpp image_processing.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
EXECUTABLE = a.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)
