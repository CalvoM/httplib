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

style:
	find . -iname "*.h" -o -iname "*.cpp" | xargs clang-format -i

submodules:
	git submodules update --recursive --remote

deps:
	sudo apt install zlib1g -y
	wget https://github.com/weidai11/cryptopp/releases/download/CRYPTOPP_8_6_0/cryptopp860.zip
	unzip cryptopp860.zip -d cryptopp
	cd cryptopp
	make static dynamic cryptest.exe
	./cryptest.exe v
	sudo make install PREFIX=/usr/local

clean:
	@rm $(prog) cryptopp cryptopp860.zip -rf
