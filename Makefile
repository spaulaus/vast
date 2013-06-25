#!/bin/make
SHELL=/bin/bash

#Define the virtual paths
vpath %.cpp src/
vpath %.hpp include/
vpath %.o obj/

#Set some of the compile options
CXX = g++
CXXFLAGS = -fPIC -g -std=c++11 -Wall $(CINCLUDEDIRS)
LDLIBS = -ldl -lpthread -lPhysConstants
CINCLUDEDIRS = -Iinclude
c++SrcSuf = cpp

#Set the name of the program to be compiled
PROGRAM = fitting
VERSION = $(shell git describe --abbrev=0 --tags)

#Define Objects
FITTINGO = fitting.o
MODELBUILDERO = ModelBuilder.o
TOFFITTERO = ToFFitter.o

#Make the object list and prefix the object directory
OBJS = $(FITTINGO) $(MODELBUILDERO) $(TOFFITTERO)
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))

ROOTCONFIG   := root-config
CXXFLAGS     += $(shell $(ROOTCONFIG) --cflags)
LDFLAGS      += $(shell $(ROOTCONFIG) --ldflags)
LDLIBS       += $(shell $(ROOTCONFIG) --libs) -lRooFit -lRooFitCore

.SUFFIXES: .$(c++SrcSuf)

all: $(OBJS_W_DIR) $(PROGRAM)

$(OBJS_W_DIR): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(PROGRAM): $(OBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/* $(PROGRAM) *~ src/*~ include/*~
