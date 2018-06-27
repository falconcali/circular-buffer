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

#define cb_size(pcb) ((pcb)->size)
#define cb_capacity(pcb) ((pcb)->capacity)

typedef struct pt_cb {
	char* buf;
	char* write;
	char* read;
	unsigned int size;
	unsigned int capacity;
} pt_cb;

pt_cb* cb_create(unsigned int capacity);
void cb_free(pt_cb* pcb);
void cb_clear(pt_cb* pcb);

unsigned int cb_write(pt_cb* pcb, const char* data, unsigned int size);
unsigned int cb_read(pt_cb* pcb, char* data, unsigned int size);
unsigned int cb_peek(pt_cb* pcb, char* data, unsigned int size);
unsigned int cb_remove(pt_cb* pcb, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif // __PT_CB_H__
