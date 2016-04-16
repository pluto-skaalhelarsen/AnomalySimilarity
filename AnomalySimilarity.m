# makefile for AnomalySimilarity exploration of the Numenta NuPIC code
CC=g++
LINK=g++
CFLAGS= -c -std=gnu++11 -I $(NUPIC_CORE)/src
LFLAGS= -std=gnu++11
LIBS= $(NUPIC_CORE)/lib/_algorithms.so  $(NUPIC_CORE)/lib/_engine_internal.so

OBJS=AnomalySimilarity.o CmdLineParse.o SpParamFile.o BufferSummary.o Sparse.o Paragon.o InputData.o
ICOMMON=

all: AnomalySimilarity

AnomalySimilarity.o : AnomalySimilarity.cpp
	$(CC) $(CFLAGS) $*.cpp

CmdLineParse.o : CmdLineParse.cpp
	$(CC) $(CFLAGS) $*.cpp


AnomalySimilarity:	$(OBJS)
	$(LINK) $(LFLAGS) -o AnomalySimilarity $(OBJS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

clean:
	rm *.o
	rm AnomalySimilarity

