#!/bin/make
SHELL=/bin/bash

#Define the virtual paths
vpath %.cpp src/
vpath %.hpp inc/
vpath %.o obj/

#Set some of the compile options
CXX = g++
CXXFLAGS = -fPIC -g -std=c++11 -Wall $(CINCLUDEDIRS)
LDLIBS = -ldl -lpthread -lPhysConstants -lSignalGenerator -lpugixml
CINCLUDEDIRS = -Iinc
c++SrcSuf = cpp

#Set the name of the program to be compiled
PROGRAM = vast

#Define Objects
#This file must contain your MAIN function
MAINO            = main.o

#The core files that are necessary for the analysis
BGTCALCULATORO   = BGTCalculator.o
CONFIGURATIONO   = Configuration.o
DECAYO           = Decay.o
EFFCALCULATORO   = EffCalculator.o
ERRORCALCULATORO = ErrorCalculator.o
FILECHECKERO	 = FileChecker.o
FILEHANDLERO     = FileHandler.o
FITHANDLERO	     = FitHandler.o
GAMMAO           = Gamma.o
INTEGRATORO      = Integrator.o
NEUTRONO         = Neutron.o
NEUTRONDENSITYO  = NeutronDensity.o
OUTPUTHANDLERO   = OutputHandler.o
PARAMCALCULATORO = ParamCalculator.o
TOFFITTERO       = TofFitter.o

#This guy controls the fitting to the simulation data
SIMTESTO         = simtest.o
SIMCONVOLUTERO   = SimConvoluter.o

#The standalone efficiency program
EFFICIENCYO = eff.o

#The program that calculates the sensitivity limit
SENSITIVITYO = sensitivity.o
LIMITFINDERO = LimitFinder.o

#Make the object list
OBJS =  $(BGTCALCULATORO) $(CONFIGURATIONO) $(DECAYO) $(EFFCALCULATORO)
OBJS += $(ERRORCALCULATORO) $(FILECHECKERO) $(FILEHANDLERO) $(FITHANDLERO)
OBJS += $(GAMMAO) $(INTEGRATORO) $(MAINO) $(NEUTRONO) $(NEUTRONDENSITYO)
OBJS += $(OUTPUTHANDLERO) $(PARAMCALCULATORO) $(TOFFITTERO)

#Objects for the compiling of the simulation stuff
SIMOBJS = $(SIMCONVOLUTERO) $(SIMTESTO) $(FILECHECKERO)

#Objects for compiling the standalone efficiency program
EFFOBJS = $(EFFICIENCYO) $(EFFCALCULATORO) $(ERRORCALCULATORO) $(NEUTRONO)

#Objects for compiling the sensitivity limit
SENSOBJS = $(SENSITIVITYO) $(LIMITFINDERO) $(DECAYO) $(BGTCALCULATORO)
SENSOBJS = $(CONFIGURATIONO) $(FILEHANDLERO) $(INTEGRATORO) $(NEUTRONO)
SENSOBJS = $(EFFCALCULATORO) $(ERRORCALCULATORO) $(PARAMCALCULATORO)

#prefix the object directory
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))
SIMOBJS_W_DIR = $(addprefix $(OBJDIR)/,$(SIMOBJS))
EFFOBJS_W_DIR = $(addprefix $(OBJDIR)/,$(EFFOBJS))
SENSOBJS_W_DIR = $(addprefix $(OBJDIR)/,$(SENSOBJS))

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

.PHONY: clean eff sim sens doc
clean:
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/*.o $(PROGRAM) ./eff ./sim ./sens *~ src/*~ inc/*~ \
	src/*.save inc/*.save *.save
eff: $(EFFOBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@
sim: $(SIMOBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@
sens: $(SENSOBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@
doc: doc/doxyfile
	@doxygen $^
