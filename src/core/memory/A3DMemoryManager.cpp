/*
* James Keats - 0971245
* EGP-425-01 - Project 01, 2/16/19
*
* I certify that this work is entirely my own. The assessor of this project
* may reproduce this project and provide copies to other academic staff,
* and/or communicate a copy of this project to a plagiarism-checking service,
* which may retain a copy of the project on its database.
*
*/
#include "A3DMemoryManager.h"

#include <cstring>
#include "core/utils/IntUtilities.h"

#ifdef _DEBUG
#define FREED_BLOCK_MARKER 0xDD
#define NEW_BLOCK_MARKER 0xCD
#define TABLE_END_MARKER 0xED
#endif


/**
 * \brief Get a byte pointer to the end of the provided node.
 */
inline byte_t* endOfNodePtr(memory_node* node)
{
	return (byte_t*)(node + 1) + node->size;
}

/**
* \brief Calculate the size between the targetNode's memory block and the end of the manager's space.
* \return The gap between the potential end of the targetNode and the end of the managed buffer.
*		Returns < 0 if the targetSize will not fit in this location, 0 if it fits perfectly, or the remaining gap.
*/
ptrdiff_t checkRemainingGap(MemoryManager* manager, memory_node* targetNode, size_t targetSize)
{
	// find the pointer to the start of the actual memory for this node.
	byte_t* start = (byte_t*)(targetNode + 1);

	// find the pointer at the end of the buffer
	void** tableEnd = (void**)((byte_t*)manager + manager->poolSize);
	void** tableStart = tableEnd - manager->allocCount;
	byte_t* end = (byte_t*)tableStart;

	// The size is the range between the pointers
	ptrdiff_t size = end - start;
	return size - targetSize;
}

/**
* \param node The node to check. Must not be null. node->next must not be null.
 * \return Greater than zero if a gap exists between the node and its next.
 */
ptrdiff_t getGapBetweenNodeAndNext(memory_node* node)
{
	byte_t* start = endOfNodePtr(node);
	byte_t* end = (byte_t*)node->next;
	ptrdiff_t gap = end - start;
	return gap;
}

/**
 * \brief Write a new node into the handle table.
 * \param manager The global manager.
 * \return A newly created handle for this node.
 */
MEM_HANDLE addNodeToTable(MemoryManager* manager)
{
	void** tableEnd = (void**)((byte_t*)manager + manager->poolSize);
	void** tableStart = tableEnd - manager->allocCount;

	MEM_HANDLE target = nullptr;
	for (target = tableEnd; target != tableStart; --target)
	{
		// Check if this table entry has previously been cleared
		if (*target == nullptr)
			break;
	}

	// If we're at the start, we need to increment our allocation count.
	if (target == tableStart)
		++manager->allocCount;

	return target;
}

/**
 * \brief Remove the handle from the handle table.
 * \return The memory_node at the start of the block this handle previously pointed to.
 */
memory_node* eraseHandleFromTable(MEM_HANDLE handle, MemoryManager* manager)
{
	byte_t* end = (byte_t*)manager + manager->poolSize;
	void** tableEnd = (void**)end;
	void** tableStart = tableEnd - manager->allocCount;

	memory_node* returnVal = (memory_node*)DEREF_MEM_HANDLE(handle) - 1;
	*handle = nullptr;

	handle = tableStart + 1;
	while (handle != (tableEnd + 1) && *handle == nullptr)
	{
		--manager->allocCount;
		++handle;
	}

	return returnVal;
}

/**
 * \brief Find the memory handle that points to a specific node.
 */
MEM_HANDLE findHandleToNode(memory_node* node, MemoryManager* manager)
{
	void** tableEnd = (void**)((byte_t*)manager + manager->poolSize);
	void** tableStart = tableEnd - manager->allocCount;

	for (MEM_HANDLE target = tableEnd; target != tableStart; --target)
	{
		if (DEREF_MEM_HANDLE(target) == node)
			return target;
	}

	return nullptr;
}

/**
 * \brief Defrag tool to move a node from one location to another.
 */
void defragMoveNode(memory_node* original, memory_node* target, MemoryManager* manager)
{
	// Grab the handle for this node so we can update it.
	MEM_HANDLE handle = findHandleToNode(original + 1, manager);
	if (handle == nullptr)
	{
		printf("ERROR: Node has no handle to it. This should not be possible.\n");
		return;
	}

	memmove(target, original, original->size + sizeof(memory_node));
	*handle = target + 1;
}

/**
 * \brief Blanks the space between the node and its next with FREED_BLOCK_MARKER.
 * If current is the tail of the list, blanks up to the handle table.
 */
void debugBlankSpaceBetweenNodes(memory_node* current, MemoryManager* manager)
{
#if _DEBUG
	byte_t* clearStart = endOfNodePtr(current); 
	byte_t* clearEnd = (byte_t*)current->next;

	if (clearEnd == nullptr)
	{
		void** tableEnd = (void**)((byte_t*)manager + manager->poolSize);
		void** tableStart = tableEnd - manager->allocCount;
		clearEnd = (byte_t*)tableStart;
	}

	ptrdiff_t rangeSize = clearEnd - clearStart;
	memset(clearStart, FREED_BLOCK_MARKER, rangeSize);
#endif
}

MemoryManager* initializeMemoryManager(void* buffer, size_t size)
{
	if (size <= sizeof(MemoryManager))
	{
		printf("Trying to initialize MemoryManager in a buffer that is too small!\n");
		return nullptr;
	}

	MemoryManager* manager = (MemoryManager*)buffer;
	manager->poolSize = size;
	manager->allocCount = 0;
	manager->head->next = nullptr;
	manager->head->size = 0;

#ifdef _DEBUG
	byte_t* tableEnd = (byte_t*)manager + manager->poolSize;
	*tableEnd = TABLE_END_MARKER;
#endif

	return manager;
}

MEM_HANDLE reserveMemory(size_t size, MemoryManager* manager)
{
	// Create a new handle for this reservation
	MEM_HANDLE newHandle = addNodeToTable(manager);

	memory_node* targetNode = nullptr;
	if (manager->head->size == 0 && manager->head->next == nullptr)
	{
		if (checkRemainingGap(manager, manager->head, size) < 0)
		{
			// If this won't fit, erase the new handle and return null.
			eraseHandleFromTable(newHandle, manager);
			return nullptr;
		}

		targetNode = manager->head;
	}
	else
	{
		memory_node* currentNode = manager->head;
		do
		{
			// Next is null and we haven't found space yet; stick it at the end.
			if (currentNode->next == nullptr)
			{
				targetNode = (memory_node*)endOfNodePtr(currentNode);
				if (checkRemainingGap(manager, targetNode, size) < 0)
				{
					// If this won't fit (and we're at the end of the chain), erase the new handle and return null.
					eraseHandleFromTable(newHandle, manager);
					return nullptr;
				}

				// We found somewhere that this fits! Set the currentNode's next to this new node.
				currentNode->next = targetNode;
				targetNode->next = nullptr;
			}
			else
			{
				// If there's a gap between this node and its next (fragmentation), see if we can insert in between here.
				if (getGapBetweenNodeAndNext(currentNode))
				{
					targetNode = (memory_node*)endOfNodePtr(currentNode);
					if (checkRemainingGap(manager, targetNode, size) < 0)
					{
						// Not enough space. Set target back to null and keep searching.
						targetNode = nullptr;
					}
					else
					{
						// A gap exists that is big enough. We can insert in the middle.
						targetNode->next = currentNode->next;
						currentNode->next = targetNode;
					}
				}
			}
			
			currentNode = currentNode->next;
		} while (targetNode == nullptr);
	}

	targetNode->size = size;

#ifdef _DEBUG
	memset(targetNode + 1, NEW_BLOCK_MARKER, targetNode->size);
#endif

	// Set the handle we made to point at the correct location and return it.
	*newHandle = (targetNode + 1);
	return newHandle;
}

void freeMemory(MEM_HANDLE handle, MemoryManager* manager)
{
	if (handle == nullptr)
		return;

	// Remove the node from the linked list
	memory_node* node = eraseHandleFromTable(handle, manager);
	if (node == nullptr)
		return;

	// Classic "remove an item from a linked list" implementation
	memory_node* follower = nullptr, *searcher = manager->head;
	while (searcher != node && searcher != nullptr)
	{
		follower = searcher;
		searcher = searcher->next;
	}

	if (searcher == nullptr)
	{
		printf("ERROR: Could not locate a node inside the list chain. This should not be possible!\n");
		return;
	}

	if (follower != nullptr)
		follower->next = searcher->next;

#if _DEBUG
	memset(searcher + 1, FREED_BLOCK_MARKER, searcher->size);
#endif
	searcher->size = 0;
}


void defragMemory(MemoryManager* manager)
{
	// If we have 1 (or 0) nodes, we can't defrag. Quit early.
	if (manager->head->next == nullptr)
	{
#if _DEBUG
		debugBlankSpaceBetweenNodes(manager->head, manager);
#endif
		return;
	}

	// Gap in the head must be handled specially
	// If it's empty but it has a next, just move the next node to the head.
	if (manager->head->size == 0)
	{
		defragMoveNode(manager->head->next, manager->head, manager);
	}

	memory_node* current = manager->head;
	while (current != nullptr && current->next != nullptr)
	{
		if (getGapBetweenNodeAndNext(current))
		{
			// gap exists between this node and its next. Move the next "backwards" to the end of our buffer.
			memory_node* newPosition = (memory_node*)endOfNodePtr(current);
			defragMoveNode(current->next, newPosition, manager);

#if _DEBUG
			debugBlankSpaceBetweenNodes(newPosition, manager);
#endif
			current->next = newPosition;
		}

		current = current->next;
	}
}

size_t getFragmentationAmount(MemoryManager* manager)
{
	// If there are 1 (or 0) nodes, we cannot have any fragmentation.
	if (manager->head->next == nullptr)
	{
		return 0;
	}

	size_t result = 0;
	memory_node* current = manager->head;

	while (current != nullptr && current->next != nullptr)
	{
		result += getGapBetweenNodeAndNext(current);
		current = current->next;
	}

	return result;
}
