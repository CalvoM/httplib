run: build
	@./httpclient
	
build:
	@g++ *.cpp Client/*.cpp sharedlibs/network/*.cpp -I . -I Client/ -I sharedlibs/network/ -o httpclient

clean:
	@rm httpclient