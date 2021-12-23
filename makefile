CC=gcc
PDIR= ../

chat: chat.c $(PDIR)Server_Functions.c
	$(CC)  $< $(PDIR)Server_Functions.c -o $@
