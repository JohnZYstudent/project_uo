CXX = g++
CXXFLAGS = -g -std=c++14 
# Uncomment the CXXFLAGS definition below to use the parallel MR runtime
# CXXFLAGS = -g -std=c++14 -pthread -Wl,--no-as-needed -DPARALLEL_MR

all: test-wordCount.exe test-sentenceStats.exe

%.o : %.cpp mr.hpp
	$(CXX) -c $< $(CXXFLAGS) 

WC_OBJECTS = test-wordCount.o wordCount.o ioutils.o	
test-wordCount.exe: $(WC_OBJECTS)
	$(CXX) -o $@ $(WC_OBJECTS) $(CXXFLAGS)
	
SS_OBJECTS = test-sentenceStats.o sentenceStats.o ioutils.o	
test-sentenceStats.exe: $(SS_OBJECTS)
	$(CXX) -o $@ $(SS_OBJECTS) $(CXXFLAGS)

PH_OBJECTS = test-phrases.o phrases.o ioutils.o	
test-phrases.exe: $(PH_OBJECTS)
	$(CXX) -o $@ $(PH_OBJECTS) $(CXXFLAGS)

clean:
	$(RM) *.o *.exe
