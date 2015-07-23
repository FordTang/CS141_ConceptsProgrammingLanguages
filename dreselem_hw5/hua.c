void *allocate(ARENA *arena, int size) {
	// TODO round up size to next multiple of CHUNK_SIZE
	int adjsize = roundup(size);
	// TODO follow list entries (starting at arena->head) until appropriate sized slot is found
	// Hint: For traversing the list, check out the printArena code above

	METAENTRY *slot = arena->head;

	while((char*)slot < (char*)arena->memory + arena->size)
	{
		// TODO If slot is occupied, go to next slot
		if(slot->status == 1)
		{
			slot = (METAENTRY*)((char*) slot + CHUNK_SIZE + slot->size);
		}
		// TODO If slot is too small, go to next slot
		else if(slot->size < adjsize)
		{
			slot = (METAENTRY*)((char*) slot + CHUNK_SIZE + slot->size);

		}
		// TODO If slot can fit `size` but cannot be split, set it as occupied
		else if (slot->size == adjsize)
		{
			slot->status = 1;
			// TODO METAENTRY
			slot = (METAENTRY*)((char*) slot + CHUNK_SIZE);

			return slot;
		}
		// TODO Otherwise, split it and add set the first part as occupied
		else if (slot->size > adjsize)
		{
			METAENTRY *adjslot =  (METAENTRY*)((char*)slot + CHUNK_SIZE + adjsize);
			adjslot->status = 0;
			adjslot->size = slot->size - adjsize - CHUNK_SIZE;
			slot->size = adjsize;
			slot->status = 1;
			slot = (METAENTRY*)((char*) slot + CHUNK_SIZE);

			return slot;
		}
		// TODO If no memory can be found, return 0

	}

	return 0;





}