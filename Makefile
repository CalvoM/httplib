run:
	@g++ *.cpp Client/*.cpp sharedlibs/network/*.cpp -I . -I Client/ -I sharedlibs/network/ && ./a.out