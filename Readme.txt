Simple NuPIC C++ Spatial Pooler with File-based Data Sets with Similarity for a Simple Classifier

This is another extension of the Numenta NuPIC C++ core library example code. It uses the Spatial Pooler (SP) only, and generates random data set that overlap in content and displays the results. A (very) simple classifier estimates the probability that the final data sequence matches the learned sequence.

The NuPIC SP parameters can be read from a text file, which is optionally named on the command line. By pre-constructing a variety of parameter files, the command line can be used to construct random input data sets of various sizes, probe the learning progress of the SP, and examine the classifier and SP output. The artificial induced overlap represents similarity between adjacent data frames which is reflected in the classifier distributions.

NuPIC is an open source project providing a computer model of algorithms originating from analysis of the neurobiology of the mammalian neocortex. For more information, see numenta.org. Although much of the research at Numenta is done in Python, the core algorithms are available in a C++ implementation.  This code links to the NuPIC libraries _algorithms.so and _engine_internal.so available at numenta.org. If you are looking for a simple way to access this development environment, you might peruse the instructions titled "Cheater's Guide..." on this site.My environment is Linux with Gnu C++ 4.8 or higher, but others also work. See the numenta.org documents.

The AnomalySimilarity program is not a user application. It is a programmer's tool. Although minimal programming skill is required to compile and run the program and experiment with the HTM concepts, the primary audience is programmers, who will also experiment with it "as is" before hacking at the interesting bits themselves. As such, the code is somewhat oversimplified and obvious, specifically to make it more malleable. If the admittedly primitive component is inadequate for your purposes, drop in one of the many devices out there, and hack away. That's my attitude. I do it, and have many different versions. This is the generic, transparent version.

That said, it is pretty simple, really. There's a makefile named AnomalySimilarity.m (make -e -f AnomalySimilarity.m) that is set up for the environment described in the Cheater's Guide. That environment is also simple and is essentially a Python virtual env, only I just use it as a way of setting the library path, etc. If you've set that up, there is a tiny script named Setup.sh (source Setup.sh) that activates the virtual env in preparation for the make. The venv also helps the Linux loader find the Numenta shared libraries in a local directory.

Overview of the Program Usage

The AnomalySimilarity program is a copy of ClassifiedNoise with a few significant changes to the beginning of main(). When the AnomalySimilarity starts up, it creates an SP from the parameters in a param file, or defaults if you didn't name one on the command line. It goes into a loop for a count of Epochs invoking the SP compute function with learning enabled each pass. The data source is a sequence of data frames having 10000 points read from a file. The file can contain many more frames of data than the SequenceCount, so you can create a large file and experiment with a variety of smaller sequences.

So, you can set both the Epochs and the SequenceCount (the number of frames) from the command line. SequenceCount is clipped at 10000, just as a general precaution, but more frames should be possible. If SequenceCount is much smaller than Epochs you get many repeated sequences of the same random patterns. The number of patterns in the set is SequenceCount. If you don't really care what the pattern is, random is good, then you can experiment with a lot of variations quickly with this technique.

At the end of the learning cycle is one more pass through the SP compute cycle for each pattern in the set, that is, it runs through once for each pattern with the SP leaning disabled. One final pass over the pattern set is made executing the SP compute step, this time running each SP output through a simple classifier that  computes the degree of match between that output and the original input pattern set. That match-ness can be printed as a real number loosely indicating confidence in the best match it finds.

For a more detailed look at the changing SP outputs for each pattern during the learning cycle, you can use a command line flag to --display_while_learning. The options available on the command line are only a very basic set. The C++ class that processes them is pretty easy to add to and the places in the main program where these are used stand out, since the command line string is named when the value is retrieved. The param file code is very similar, if you want to add parameters that are not strictly part of the SP initialization.

Command Line Usage

There is a text file named Test.par that is a parameter file with the normal default parameters for the Spatial Pooler constructor. Look at the file SpParamFile.cpp in the routine InitTables() to see the names of the fields in the text file (they are the same as the NuPIC variable names) and their local default values. I typically copy and rename several param files and change parameters in each, then pull them into the program using --SpParams=Test.par on the command line.

The number of compute iterations in the learning cycle is called the learning epochs and is set from the command line as: --Epochs=500 or whatever. A large, complex pattern set might require several thousand iterations.

The input pattern set is read in from a data file which can be specified on the command line something like --InputData=Test.dat. The number of input pattern buffers in the set is controlled from the command line with: --SequenceCount=6 or whatever. the larger this count, the more patterns in your set.

A typical usage is:

./AnomalySimilarity --sp_summary --Epochs=500 --SequenceCount=6 --display_while_learning --classify --InputData=Test.dat



