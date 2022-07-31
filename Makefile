
NAME = monitoring

CC = gcc

SRCS = main.c http.c 

OBJS = $(SRCS:.c=.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME) -lcurl

%.o: %.c
	$(CC) -c $< -o $@

clean: 
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re