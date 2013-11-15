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
PROGRAM = vast

#Define Objects
#This file must contain your MAIN function
MAINO              = ex.o

BGTCALCULATORO   = BGTCalculator.o
DECAYO           = Decay.o
EFFCALCULATORO   = EffCalculator.o
ERRORCALCULATORO = ErrorCalculator.o
FILECHECKERO     = FileChecker.o
SIMTESTO         = simtest.o
INTEGRATORO      = Integrator.o
LIMITFINDERO     = LimitFinder.o
NEUTRONO         = Neutron.o
NEUTRONDENSITYO  = NeutronDensity.o
PARAMCALCULATORO = ParamCalculator.o
SIMCONVOLUTERO   = SimConvoluter.o
TOFFITTERO       = TofFitter.o

#Make the object list
OBJS =  $(BGTCALCULATORO) $(DECAYO) $(EFFCALCULATORO) $(ERRORCALCULATORO)
OBJS += $(MAINO) $(FILECHECKERO) $(INTEGRATORO) $(LIMITFINDERO) $(NEUTRONO)
OBJS += $(NEUTRONDENSITYO) $(PARAMCALCULATORO) $(SIMCONVOLUTERO) $(TOFFITTERO)

#prefix the object directory
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))

#Add the ROOT config stuff to the compilation
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

.PHONY: clean eff
clean: 
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/* $(PROGRAM) ./eff *~ src/*~ include/*~
eff: src/eff.cpp $(EFFCALCULATORO) $(ERRORCALCULATORO) $(NEUTRONO)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@
