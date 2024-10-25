all: sum_serial sum_multi_thread

# Compile the serial version
sum_serial: sum_serial.c
	gcc -Wall -o sum_serial sum_serial.c

# Compile the multi-threaded version
sum_multi_thread: sum_multi_thread.c
	gcc -Wall -pthread -o sum_multi_thread sum_multi_thread.c

# Clean up generated files
clean:
	rm -f sum_serial sum_multi_thread
