# Vandle Analysis Software Toolkit (VAST)
I (S. V. Paulauskas) wrote VAST to analyze data for my thesis. This software was written and designed to analyze data
 from small VANDLE bars. I do not currently have support for the medium bars without changing a bunch of magic 
 numbers. I will (hopefully) soon be updating this to handle a lot of things better than they are now.  

## Some prerequisites:
* ROOT >= 6
* RooFit >= 3.55
* Cmake > 3.1

1. SETTING UP 
   A) Directory structure:
      I have been using the following directory structure: data, pics/tof, pics/vast, 
      results/tof, results/vast. These have been working pretty well for me but 
      that does not mean it works for you. The configuration file requires that 
      you put in path names into the files so that there is no need to have a set 
      directory structure. While this seems inflexible, the idea is that you're 
      going to have to think about what you're putting into this thing. 
      
   B) Config.xml :
      The idea here is that the ConfigParser is going to parse out all the little 
      bits for the various classes. There will be several classes that only hold 
      information about the setup (paths/etc) and about the experiment (number 
      of bars, solid angle coverage, beta efficiency, etc.).