#!/bin/make
SHELL=/bin/bash

#Define the virtual paths
vpath %.cpp src/
vpath %.hpp inc/
vpath %.o obj/

#Set some of the compile options
CXX = g++
CXXFLAGS = -fPIC -g -std=c++11 -Wall $(CINCLUDEDIRS)
LDLIBS = -ldl -lpthread -lPhysConstants -lSignalGenerator
CINCLUDEDIRS = -Iinc
c++SrcSuf = cpp

#Set the name of the program to be compiled
PROGRAM = analyze

#Define Objects
BGTCALCULATORO = BGTCalculator.o
DECAYO = Decay.o
EFFCALCULATORO = EffCalculator.o
EXO = ex.o
INTEGRATORO = Integrator.o
NEUTRONO = Neutron.o
NEUTRONDENSITYO = NeutronDensity.o

#Make the object list and prefix the object directory
OBJS =  $(BGTCALCULATORO) $(DECAYO) 
OBJS += $(EFFCALCULATORO) $(EXO) $(INTEGRATORO) $(NEUTRONO)
OBJS += $(NEUTRONDENSITYO)
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))

.SUFFIXES: .$(c++SrcSuf)

all: $(OBJS_W_DIR) $(PROGRAM)

$(OBJS_W_DIR): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(PROGRAM): $(OBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean eff
clean: 
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/* $(PROGRAM) ./eff *~ src/*~ include/*~
eff: src/eff.cpp $(EFFCALCULATORO)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@
