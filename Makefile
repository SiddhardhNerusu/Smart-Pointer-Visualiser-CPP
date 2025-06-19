all:
	g++ -std=c++17 -Iinclude src/main.cpp -o smart_ptr_test

run:
	./smart_ptr_test
