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
#pragma once
#include <stddef.h>
#include <stdio.h>

#define MEM_HANDLE void**
#define DEREF_MEM_HANDLE(val) (*val)

struct memory_node
{
	memory_node* next;
	size_t size;
};

struct MemoryManager
{
	size_t poolSize, allocCount;
	memory_node head[1];
};

/**
 * \brief Purpose: prime a block of memory to be managed.
 * \param buffer The memory address of the buffer to be managed.
 * \param size The size (in bytes) of the buffer.
 * \return A new MemoryManager to manage the provided buffer, or NULL if the initialization failed.
 */
MemoryManager* initializeMemoryManager(void* buffer, size_t size);

/**
 * \brief Purpose: Search for an open gap in the managed block and mark it as reserved, then return it.
 * \param size The size of the block to reserve.
 * \param manager The manager for the section of memory we are searching.
 * \return A pointer to the new area, or NULL if one could not be made.
 */
MEM_HANDLE reserveMemory(size_t size, MemoryManager* manager);

/**
 * \brief Purpose: mark a section of memory as open.
 * \param handle The pointer to the reserved memory chunk.
 * \param manager The manager for the section of memory we are searching.
 */
void freeMemory(MEM_HANDLE handle, MemoryManager* manager);
	
/**
 * \brief Immediately defragment this memory block by collapsing any gaps between blocks.
 * \param manager The manager for the section of memory we are defragging.
 */
void defragMemory(MemoryManager* manager);

/**
 * \brief Returns the amount of fragmentation (in bytes) present in the section of memory managed by this manager.
 * Fragmentation is defined as the size of gaps between the different reserved buffers.
 */
size_t getFragmentationAmount(MemoryManager* manager);
