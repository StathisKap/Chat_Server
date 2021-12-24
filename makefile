CC=gcc

chat: chat.c $(PDIR)Server_Functions.c
	$(CC)  $< Server_Functions.c -o $@
