/***********************************************************************************
The MIT License (MIT)

Copyright (c) 2018 Falcon Cali

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
***********************************************************************************/

#include <memory.h>
#include <stdlib.h>
#include "pt_cb.h"

pt_cb* cb_create(unsigned int capacity)
{
	if (capacity == 0)
		return NULL;

	pt_cb* pcb = (pt_cb*)malloc(sizeof(pt_cb));
	if (pcb == NULL)
		return NULL;

	pcb->buf = (char*)malloc(capacity);
	if (pcb->buf == NULL)
	{
		free(pcb);
		return NULL;
	}

	pcb->write = pcb->read = pcb->buf;
	pcb->size = 0;
	pcb->capacity = capacity;
	
	return pcb;
}

void cb_free(pt_cb* pcb)
{
	free(pcb->buf);
	free(pcb);
}

void cb_clear(pt_cb* pcb)
{
	pcb->size = 0;
	pcb->write = pcb->read = pcb->buf;
}

unsigned int cb_write(pt_cb* pcb, const char* src_buffer, unsigned int size)
{
	unsigned int bytes_can_write = pcb->capacity - pcb->size;
	if (size > bytes_can_write) 
		size = bytes_can_write;
	unsigned int byte_to_end = pcb->capacity - (pcb->write - pcb->buf);
	if (byte_to_end > size)
	{
		memcpy(pcb->write, src_buffer, size);
		pcb->write += size;
	}
	else
	{
		memcpy(pcb->write, src_buffer, byte_to_end);
		unsigned int byte_left = size - byte_to_end;
		memcpy(pcb->buf, src_buffer + byte_to_end, byte_left);
		pcb->write = pcb->buf + byte_left;
	}

	pcb->size += size;
	return size;
}

unsigned int cb_read(pt_cb* pcb, char* dst_buffer, unsigned int size)
{
	if (size > pcb->size) 
		size = pcb->size;
	unsigned int byte_to_end = pcb->capacity - (pcb->read - pcb->buf);
	if (byte_to_end > size)
	{
		memcpy(dst_buffer, pcb->read, size);
		pcb->read += size;
	}
	else
	{
		memcpy(dst_buffer, pcb->read, byte_to_end);
		unsigned int byte_left = size - byte_to_end;
		memcpy(dst_buffer + byte_to_end, pcb->buf, byte_left);
		pcb->read = pcb->buf + byte_left;
	}

	pcb->size -= size;
	return size;
}

unsigned int cb_peek(pt_cb* pcb, char* dst_buffer, unsigned int size)
{
	if (size > pcb->size) 
		size = pcb->size;
	unsigned int byte_to_end = pcb->capacity - (pcb->read - pcb->buf);
	if (byte_to_end > size)
	{
		memcpy(dst_buffer, pcb->read, size);
	}
	else
	{
		memcpy(dst_buffer, pcb->read, byte_to_end);
		memcpy(dst_buffer + byte_to_end, pcb->buf, size - byte_to_end);
	}

	return size;
}

unsigned int cb_remove(pt_cb* pcb, unsigned int size)
{
	if (size > pcb->size) 
		size = pcb->size;
	unsigned int byte_to_end = pcb->capacity - (pcb->read - pcb->buf);
	if (byte_to_end > size)
	{
		pcb->read += size;
	}
	else
	{
		pcb->read = pcb->buf + size - byte_to_end;
	}

	pcb->size -= size;
	return size;
}