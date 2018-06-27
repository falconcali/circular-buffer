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

#ifndef __PT_CB_H__
#define __PT_CB_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pt_cb {
	char* buf;
	char* write;
	char* read;
	unsigned int size;
	unsigned int capacity;
} pt_cb;

/* Create a circular buffer with given capacity.
 *
 * Param capacity defines the max bytes that the circular buffer can hold. If the buffer
 * is full, extra bytes will be ignored. This param should not be 0.
 *
 * Returns a circular buffer pointer, will be NULL if memory allocation failed 
 * or the given capacity is set to 0.
 */
pt_cb* cb_create(unsigned int capacity);

/* Free the given circular buffer.*/
void cb_free(pt_cb* pcb);

/* Clear all bytes in the given circular buffer. */
void cb_clear(pt_cb* pcb);

/* Write bytes into the given circular buffer.
 * 
 * Returns the actual size that has been written. This value will be less than 
 * the given size if the circular buffer is full, and the extra bytes will be
 * ignored.
 */
unsigned int cb_write(pt_cb* pcb, const char* src_buffer, unsigned int size);

/* Read bytes from the given circular buffer. 
 *
 * Returns the actual size that has been read. This value will be less than
 * the given size if the circular buffer size is less than given size.
 */
unsigned int cb_read(pt_cb* pcb, char* dst_buffer, unsigned int size);

/* Peek bytes from the given circular buffer.
 *
 * This function do not change the circular buffer size. Usually used to check
 * some head bytes to determine how many bytes will be read.
 *
 * Returns the actual size that has been Peek. This value will be less than
 * the given size if the circular buffer size is less than given size.
 */
unsigned int cb_peek(pt_cb* pcb, char* dst_buffer, unsigned int size);

/* Remove bytes from the given circular buffer.
 *
 * Returns the actual size that has been Removed. This value will be less than
 * the given size if the circular buffer size is less than given size.
 */
unsigned int cb_remove(pt_cb* pcb, unsigned int size);

/* Returns the size of given circular buffer. */
#define cb_size(pcb) ((pcb)->size)

/* Returns the capacity (max size) of given circular buffer. */
#define cb_capacity(pcb) ((pcb)->capacity)

#ifdef __cplusplus
}
#endif

#endif // __PT_CB_H__
