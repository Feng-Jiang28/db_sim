# Makefile
all: main 

main: src/main.cpp src/Database.cpp src/QueryLanguage.cpp src/Utils.cpp
	g++ -o main src/main.cpp src/Database.cpp src/QueryLanguage.cpp src/Utils.cpp -I include/ -std=c++17

clean: 
	rm main