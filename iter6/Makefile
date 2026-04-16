CXX      = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

# Platform detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    LDFLAGS = -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
else ifeq ($(OS),Windows_NT)
    LDFLAGS = -lfreeglut -lopengl32 -lglu32
else
    LDFLAGS = -lGL -lGLU -lglut
endif

# Override with: make PLATFORM=macos  or  make PLATFORM=mingw
ifeq ($(PLATFORM),macos)
    LDFLAGS = -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
endif
ifeq ($(PLATFORM),mingw)
    LDFLAGS = -lfreeglut -lopengl32 -lglu32
endif

SRCS    = $(shell find src -name "*.cpp")
OBJS    = $(SRCS:.cpp=.o)
TARGET  = shuttle

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Isrc -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
