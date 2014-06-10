/** \file doxygenMainPage.hpp
 *\brief Dummy file for Doxygen structure
 */

/** \mainpage Pixie16 Analysis 

  \author S. V. Paulauskas
  \version code : v0.6.0 \n
  manual : beta v1

  Contact : stanpaulauskasATgmailDOTcom
    

  This manual documents the workings of the Vandle Analysis Software Toolkit 
  (V.A.S.T.). This thing is in no way comprehensive or complete. However, I will 
  do my best to make sure that it's in some way useful.

  I have blatantly stolen some pieces of this manual from the pixie_scan codes 
  developed at The University of Tennessee at Knoxville, which was written in 
  large part by S. N. Liddick and D. Miller.
  
  To start you off here is some information about the \subpage introduction
*/

/* \page introduction Introduction
  There are two main files which control the pixie16 analysis flow,
  PixieStd.cpp and DetectorDriver.cpp both of which are located
  in the src directory.  The functions in PixieStd.cpp reconstruct a
  complete data spill from the pixie16 modules and, for each spill, 
  create a list of channels that triggered.  The list is then sorted
  according to time and those channels which occur close to each other
  in time are grouped together into events.  The event is then passed
  into DetectorDriver.cpp for processing.

  DetectorDriver.cpp receives each event and calibrates the energy for
  each channel in the event.  The raw and calibrated energies are plotted
  if the appropriate damm spectra have been created in DeclareHistogram.cpp.
  Lastly, experiment specific analysis is performed. Experiment specific
  analysis for generic MTC and RMS experiments remains unimplemented in the
  current version.
*/
