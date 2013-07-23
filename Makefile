INCLUDE_DIR=include
SOURCE_DIR=src
BUILD_DIR=build
HEADERS=$(wildcard $(INCLUDE_DIR)/*.h)
SOURCES=$(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS=$(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
EXE=$(BUILD_DIR)/main
RM=/bin/rm -rf

#SDL configuration
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LIBS := $(shell sdl-config --libs) -lSDL_image \
    -lSDL_mixer -lSDL_ttf

CC=g++
CFLAGS=-c -Wall

INCLUDES=-I$(INCLUDE_DIR) $(SDL_CFLAGS)
LIBS=$(SDL_LIBS)

all: $(EXE)# run

#run:
#	./$(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	$(RM) $(BUILD_DIR)/*.o

.PHONY: clean
	
