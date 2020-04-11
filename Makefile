submarine: main.cpp
	c++ -std=c++2a -o submarine main.cpp -I/usr/local/include

install: submarine
	install submarine /bin/
