TARGETS=heapstack

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

%: %.c
	gcc -Wall -o $@ $<