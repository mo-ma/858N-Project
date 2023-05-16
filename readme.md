To compile the code using using gcc, use a c++ version at least as recent as c++17 and use the -pthread argument. For example, the following command can be used to compile the tester code and run the specified tests:
``` 
g++ -std=c++17 -pthread tester.cpp
``` 
The tester uses a hardcoded list of input files and tests the three implementations on each of them, and records the running times in the specifed output file using csv formatting.
As parlay is used for the implementation, variable PARLAY_NUM_THREADS can be used to set the number of threads used.
The tests used in the reported performance checks have been zipped before uploading and should be unzippedto be used.
