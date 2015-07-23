//Ford Tang
//46564602
//CS 141
//Homework 5

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define CHUNK_SIZE 64 // granularity - all allocated objects take at least this many bytes, must be at least sizeof(METAENTRY)

typedef struct METAENTRY {
	int size;
	char status; // either 0 for free or 1 for occupied
} METAENTRY;

typedef struct ARENA {
	void *memory;
	int size;
	METAENTRY *head;
} ARENA;

void printArena(ARENA *arena) {
	printf("[");

	METAENTRY *slot = arena->head;
	while((char*)slot < (char*)arena->memory + arena->size) {
		printf("M");
		for(int i = 0; i < slot->size / CHUNK_SIZE; ++i) {
			printf("%c", (slot->status ? 'X' : ' '));
		}
		slot = (METAENTRY*)((char*) slot + CHUNK_SIZE + slot->size);
	}

	printf("]\n");
}

void printPositionInArena(ARENA *arena, void *addr) {
	printf(" ");
	int slot = ((char*)addr - (char*)arena->memory) / CHUNK_SIZE;
	for(int i = 0; i < slot; ++i) printf(" ");
	printf("^\n");
    //printf("address: %i, memory: %i\n", (int)addr, (int)arena->memory);
}

// TODO Your part starts here - you won't have to modify anything above.

ARENA* createArena(int size) {
	assert(size % CHUNK_SIZE == 0);
	assert(sizeof(METAENTRY) < CHUNK_SIZE);

	// TODO allocate memory (using malloc) and set ARENA struct
	ARENA* arena = (struct ARENA*) malloc(sizeof(struct ARENA));
	arena->memory = (char*) malloc(size);
	arena->size = size;

	// TODO write METAENTRY at beginning of allocated memory and set size (hint: cast the memory that you allocated into a METAENTRY*
	arena->head = (METAENTRY*) arena->memory;
    arena->head->size = size - CHUNK_SIZE;	
    arena->head->status = 0;

	return arena;
}

void *allocate(ARENA *arena, int size) {
	// TODO round up size to next multiple of CHUNK_SIZE
	//if (size < CHUNK_SIZE)
    printf("size: %i\n", size);
    if (size > CHUNK_SIZE)
            size = (size / CHUNK_SIZE) * CHUNK_SIZE + CHUNK_SIZE;
    else
        size = CHUNK_SIZE;
    printf("new size: %i\n", size);
	// TODO follow list entries (starting at arena->head) until appropriate sized slot is found
	// Hint: For traversing the list, check out the printArena code above

    bool found = false;
    METAENTRY *slot = arena->head;
    while((char*)slot < (char*)arena->memory + arena->size) {
        if (slot->status == 0 && slot->size > size) {
            found = true;
            break;
        }
        slot = (METAENTRY*)((char*) slot + CHUNK_SIZE + slot->size);
    }

    if (found) {
        if (slot->size > size + CHUNK_SIZE) {
            METAENTRY *newmeta = (METAENTRY*)((char*) slot + CHUNK_SIZE + size);
            newmeta->size = slot->size - size - CHUNK_SIZE;
            newmeta->status = 0;
            if (size == CHUNK_SIZE) {
                slot->size = size;
            }
            else
                slot->size = size - CHUNK_SIZE;
        }
        slot->status = 1;
        return (METAENTRY*)((char*) slot + CHUNK_SIZE);
    }

    /* 
    METAENTRY *slot = arena->head;
    while ((char*)slot < (char*)arena->memory + arena->size) {
    // TODO If slot is occupied, go to next slot
        if (slot->status == 1)
            slot = (METAENTRY*)((char*) slot + CHUNK_SIZE + slot->size);
	// TODO If slot is too small, go to next slot
        else if (slot->size < size)
            slot = (METAENTRY*)((char*) slot + CHUNK_SIZE + slot->size);
	// TODO If slot can fit `size` but cannot be split, set it as occupied
        else if (slot->size == size) {
            slot->status = 1;
            return (METAENTRY*)((char*) slot + CHUNK_SIZE);
        }
	// TODO Otherwise, split it and add set the first part as occupied
        else if (slot->size > size) {
            METAENTRY *newmeta = (METAENTRY*)((char*) slot + CHUNK_SIZE + size);
            newmeta->size = slot->size - size - CHUNK_SIZE;
            newmeta->status = 0;
            if (size == CHUNK_SIZE)
                slot->size = size;
            else
                slot->size = size - CHUNK_SIZE;
            slot->status = 1;
            return (METAENTRY*)((char*) slot + CHUNK_SIZE);
        }
	}
    */

    // TODO If no memory can be found, return 0
	return 0;
}

void coalesce(ARENA *arena) {
	// TODO find free entries that follow each other and join them
}

void deallocate(ARENA *arena, void *addr) {
	// TODO find appropriate entry in list and set its status to 0
}

void deleteArena(ARENA *arena) {
	// TODO free up the memory that you allocated before
}

int main () {
	ARENA *arena = createArena(64 * CHUNK_SIZE);

	printf("BEGIN\n");
	printArena(arena);

	printf("\nALLOC a\n");
	void *a = allocate(arena, 10);
	printArena(arena);
	printPositionInArena(arena, a);

	printf("\nALLOC b\n");
	void *b = allocate(arena, 128);
	printArena(arena);
	printPositionInArena(arena, b);

	printf("\nALLOC c\n");
	void *c = allocate(arena, 267);
	printArena(arena);
	printPositionInArena(arena, c);

	printf("\nDEALLOC a\n");
	deallocate(arena, a);
	printArena(arena);

	printf("\nDEALLOC c\n");
	deallocate(arena, c);
	printArena(arena);

	printf("\nALLOC d\n");
	void *d = allocate(arena, 10);
	printArena(arena);
	printPositionInArena(arena, d);

	printf("\nDEALLOC b\n");
	deallocate(arena, b);
	printArena(arena);

	printf("\nALLOC e\n");
	void *e = allocate(arena, 10);
	printArena(arena);
	printPositionInArena(arena, e);

	printf("\nDEALLOC e\n");
	deallocate(arena, e);
	printArena(arena);

	printf("\nALLOC f\n");
	void *f = allocate(arena, 3000);
	printArena(arena);
	printPositionInArena(arena, e);

	printf("\nALLOC g\n");
	void *g = allocate(arena, 100);
	printArena(arena);
	printPositionInArena(arena, g);

	printf("\nALLOC h\n");
	void *h = allocate(arena, 300);
	printArena(arena);
	printPositionInArena(arena, h);

	printf("\nALLOC i\n");
	void *i = allocate(arena, 200);
	printArena(arena);
	printPositionInArena(arena, i);

	printf("\nDEALLOC d\n");
	deallocate(arena, d);
	printArena(arena);

	printf("\nDEALLOC f\n");
	deallocate(arena, f);
	printArena(arena);

	printf("\nDEALLOC g\n");
	deallocate(arena, g);
	printArena(arena);

	printf("\nDEALLOC h\n");
	deallocate(arena, h);
	printArena(arena);

	printf("\nDEALLOC i\n");
	deallocate(arena, i);
	printArena(arena);

	deleteArena(arena);

	return 0;
}
