CC	:= gcc
CFLAGS	:= -Wall -Wextra 
CFILES	:= main.c create_prog.c
LIBS	:= libmlx_Linux.a -lX11 -lXext
NAME	:= drawboard
DBGNAME	:= drawboard_debug

all: $(NAME)

debug: $(DBGNAME)

$(NAME): $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME) $(LIBS)

$(DBGNAME): $(CFILES)
	$(CC) $(CFLAGS) -g $(CFILES) -o $@ $(LIBS)

re: clean all

clean:
	rm -f $(NAME)
