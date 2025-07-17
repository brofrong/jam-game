# GNU makefile

# User configuration
CXXFLAGS ?= -Og -std=c++17 -Iinclude
LDFLAGS ?= -lSDL2
TARGET = eulamadness

# System configuration
include Makefile.srcs

EXE = $(TARGET)
OBJS = $(SRCS:.cpp=.o)

# Targets
all: $(EXE)

dist: $(EXE)
	mkdir -p dist
	cp $(EXE) dist/

$(EXE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -rf $(OBJS) $(EXE) dist
