PROJECT = CASTLE_BATTLE
WORKDIR = `pwd`

#Paths

SOURCE_PATH = ./src/
BIN_PATH = ./bin/
IRRLICHT_INCLUDE_PATH = ../Engine/include
BULLET_INCLUDE_PATH = /usr/local/include/bullet

#Compiler options

CXX = g++
CXXFLAGS = -std=c++11 -Wall
CXXFLAGS_DEBUG = $(CXXFLAGS) -g
CXXFLAGS_RELEASE = $(CXXFLAGS) -O

#Library path

BASELIBDIR = -L/usr/local/lib

#Irrlicht library path

IRRLICHT_LIB_DIR = -L../Engine/lib/Linux

#Linker flags

LDFLAGS = -lIrrlicht -lGL -lX11 -lXext -lXxf86vm -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

#Directories of the project

SUBDIRS := $(shell ls -d $(SOURCE_PATH)*/)
DIRS = ./ $(SUBDIRS) #add the current dir

#Get all the cpp files

SOURCES := $(foreach d, $(DIRS), $(wildcard $(d)*.cpp))
#Generate object files names

OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

#Generate dependencies

DEPENDENCIES = $(patsubst %.cpp, %.depend, $(SOURCES))


#Prepend -I to INCLUDE directories for the compiler

INCLUDE_SUBDIRS := $(foreach d, $(DIRS), -I$d)

#Include all up together

INCLUDE := $(INCLUDE_SUBDIRS) -I$(IRRLICHT_INCLUDE_PATH) -I$(BULLET_INCLUDE_PATH)

#Compose linker options
LIBDIR =  $(BASELIBDIR) $(IRRLICHT_LIB_DIR) $(LDFLAGS)

#Output variables

OUT_DEBUG = bin/Debug/
OUT_RELEASE = bin/Release/


#Generate dependecy files
%.depend: %.cpp
	$(CXX) -MM $< -MT "$*.o $*.depend" -MF $*.depend


#DEFAULT TARGET is set to release mode 

all: $(DEPENDENCIES) release



release: before_release out_release after_release

out_release: before_release $(OBJECTS)
	$(CXX) $(CXXFLAGS_RELEASE) -o $(OUT_RELEASE)$(PROJECT) $(OBJECTS) $(LIBDIR) $(INCLUDE)
#Include dependecies 
ifneq "$(strip $(DEPENDENCIES))" "" 
 -include $(DEPENDENCIES)
endif
%.o: %.cpp
	$(CXX) $(CXXFLAGS_RELEASE) -c $< -o $@ $(INCLUDE)


#debug: before_debug out_debug after_debug

#out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	#$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG) -include $(DEPENDENCIES)





.PHONY: before_debug after_debug clean_debug before_release after_release clean_release clean clean_depend


#Prepare and PHONY targets

clean: clean_debug clean_release

clean_depend:
	rm -f $(DEPENDENCIES)

clean_release: 
	rm -f $(OBJECTS)

before_release:
	@echo "Checking directories"
	test -d $(OUT_RELEASE) || mkdir -p bin/Release

after_release:
	@echo "Building finished!"

before_debug: 
	test -d $(OUT_DEBUG) || mkdir -p bin/Debug
	
after_debug:
	@echo "Debug Building finished!"

clean_debug:
	rm -f $(OBJECTS)
