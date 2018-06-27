# circular-buffer
A simple, easy to use and high performance circular buffer (ring buffer) designed for different systems.

How to use : 

	1. Create a circular buffer with size of 128 bytes : 
	
		pt_cb* pcb = cb_create(128);
		
	2. Write "hello world" into the circular buffer :
	
		cb_write(pcb, "hello world", 13);
	
	3. Read bytes from the circular buffer : 
	
		char read_buf[128];
		cb_read(pcb, read_buf, 13);
		printf("%s\n", read_buf); // output should be "hello world"

Check the pt_cb.h to see more APIs.