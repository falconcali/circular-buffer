# circular-buffer
A simple, easy to use and high performance circular buffer (ring buffer) designed for different systems.

How to use : 
	
	pt_cb* pcb = cb_create(128);
	cb_write(pcb, "hello world", 13);
	
	char read_buf[128];
	cb_read(pcb, read_buf, 13);
	printf("%s\n", read_buf); // "hello world"

Check the file "pt_cb.h" to see more APIs.
