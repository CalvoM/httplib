prog := httpclient
valgrind_log := valgrind-out.txt
run: build
	@./$(prog)
	
build:
	@g++ *.cpp Client/*.cpp sharedlibs/network/*.cpp -I . -I utils/ -I Client/ -I sharedlibs/network/ -lz -l:libcryptopp.a -o $(prog)

check_memory:
	chmod +x check_memory.sh 
	./check_memory.sh $(prog) $(valgrind_log)

clean:
	@rm $(prog) $(valgrind_log)