create:
	gcc main.c servtransfer.c -W -Wall -o server

start:
	./server file_to_transfer.txt

clear:
	rm server
