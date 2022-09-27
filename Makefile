all: knapsack kommi paint transport

knapsack:
	g++ knapsack.cpp -o knapsack
kommi:
	g++ kommi.cpp -o kommi
paint:
	g++ paint.cpp -o paint
transport:
	g++ transport.cpp -o transport
