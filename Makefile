S=server
P=client
CFLAGS= -g -Wall

all: $(S) $(P)X $(P)Y

$(S): $(S).cpp
	g++ $(CFLAGS) -pthread -o $(S) $(S).cpp
	
$(P)X: $(P)X.cpp
	g++ $(CFLAGS) -o $(P)X $(P)X.cpp

$(P)Y: $(P)Y.cpp
	g++ $(CFLAGS) -o $(P)Y $(P)Y.cpp
	
clean:
	rm -rf $(S)
	rm -rf $(P)X
	rm -rf $(P)Y