S=server
P=client
CFLAGS= -g -Wall

all: $(S) $(P)

$(S): $(S).cpp
	g++ $(CFLAGS) -pthread -o $(S).exe $(S).cpp
	
$(P)X: $(P)X.cpp
	g++ $(CFLAGS) -o $(P)X.exe $(P)X.cpp

$(P)Y: $(P)Y.cpp
	g++ $(CFLAGS) -o $(P)Y.exe $(P)Y.cpp
	
clean:
	rm -rf $(S).exe
	rm -rf $(P)X.exe
	rm -rf $(P)Y.exe