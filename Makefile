
NAME = monitoring

CC = gcc
INCLUDES = -I./get_next_line -I./src
RM = rm -rf

vpath %.c src get_next_line
SRCS = main.c http.c get_next_line.c get_next_line_utils.c

OBJ_DIR = ./objs
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(INCLUDES) -lcurl -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(INCLUDES) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(OBJ_DIR)
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re