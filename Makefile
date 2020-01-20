CC=clang++
CC_FLAGS=-std=c++11 -g

BINS=astar

all: $(BINS)

%: %.cc
	$(CC) $(CC_FLAGS) -o $@ $^

clean:
	rm -f $(BINS)