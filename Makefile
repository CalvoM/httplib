prog := httpclient
valgrind_log := valgrind-out.txt
test_prog := httpclient_test
cflags := Client/*.cpp sharedlibs/network/*.cpp -I utils -I Client/ -I sharedlibs/network/ -lz -l:libcryptopp.a 
run: build
	@./$(prog)
	
build:
	@g++ *.cpp $(cflags)  -o $(prog)

check_memory:
	chmod +x check_memory.sh 
	./check_memory.sh $(prog) $(valgrind_log)

test:
	@g++ tests/*.cpp $(cflags) -o $(test_prog)
	@./$(test_prog) -s -r console

clean:
	@rm $(prog) $(valgrind_log)
