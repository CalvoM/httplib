run: build
	@./httpclient
	
build:
	@g++ *.cpp Client/*.cpp sharedlibs/network/*.cpp -I . -I utils/ -I Client/ -I sharedlibs/network/ -lz -l:libcryptopp.a -o httpclient

clean:
	@rm httpclient