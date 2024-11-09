CFLAGS=-g -Wall

all: mmu_prog_t1 mmu_prog_t2

clean:
	mkdir -p build
	rm -f mmu_prog_t1 mmu_prog_t2
	rm -rf build/*

mmu_prog_t1: swap.c mmu.c fault_handler.c main.c malloc.c physical_memory.c
	$(CC) $(CFLAGS) -D$(POLICY) $(LDFLAGS) $+ -o build/$@
	
mmu_prog_t2: swap.c mmu.c fault_handler.c main_2.c malloc.c physical_memory.c
	$(CC) $(CFLAGS) -D$(POLICY) $(LDFLAGS) $+ -o build/$@
	
# Compilez le programme en utilisant 
#     make clean all POLICY=POLICY_RANDOM
#     make clean all POLICY=POLICY_FIFO
#     make clean all POLICY=POLICY_CLOCK