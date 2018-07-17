GCC_CMD=g++ -w -Wall -std=c++11
main :
	@$(GCC_CMD) -c *.cpp
	@$(GCC_CMD) main.o evtbus.o inputhdl.o sockhdl.o fifohdl.o srvhdl.o -lpthread -llog -o main
	@rm -rf *.o
	@./main
	@rm -rf main
