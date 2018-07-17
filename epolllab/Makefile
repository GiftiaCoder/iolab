GCC_CMD=g++ -w -Wall
main :
	@$(GCC_CMD) -c main.cpp
	@$(GCC_CMD) -c evtbus.cpp
	@$(GCC_CMD) -c inputhdl.cpp
	@$(GCC_CMD) -c sockhdl.cpp
	@$(GCC_CMD) -c srvhdl.cpp
	@$(GCC_CMD) main.o evtbus.o inputhdl.o sockhdl.o srvhdl.o -lpthread -llog -o main
	@rm -rf *.o
	@./main
	@rm -rf main
