WFLAGS = -W -Wall -Wextra

ROOT_INC = $(shell root-config --cflags)
ROOT_LIB = $(shell root-config --libs) -lssl # -Xlinker "-rpath=/opt/root/lib/"

CXXFLAGS = $(ROOT_INC)
LDFLAGS = -lm $(ROOT_LIB)

rout.elf: rout.cpp
	g++ $(CXXFLAGS) $(LDFLAGS) -o root.elf rout.cpp
