main: main.cpp opc_client.h
	g++  -std=c++11 -o main main.cpp

clean:
	rm main
