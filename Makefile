
NAME = monitoring

CC = gcc
INCLUDES = -I./get_next_line -I./src
RM = rm -rf

BLUE = \33[1;34m
RST = \033[0m

vpath %.c src get_next_line
SRCS = main.c http.c get_next_line.c get_next_line_utils.c ft_split.c \
		utils.c ping.c

OBJ_DIR = ./objs
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
		@ echo "$(BLUE)Compiling... $(RST)"
		@ $(CC) $(OBJS) $(INCLUDES) -lcurl -o $(NAME)
		@ echo "$(BLUE)Successfully compiled! $(RST)"

$(OBJ_DIR)/%.o: %.c
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(INCLUDES) -c $< -o $@

clean:
		@$(RM) $(OBJS)
		@ echo "$(BLUE)Objects cleaned! $(RST)"

fclean: clean
		@ $(RM) $(OBJ_DIR)
		@ $(RM) $(NAME)
		@ echo "$(BLUE)Program cleaned! $(RST)"

cfile:
		@ $(RM) monitoring.log
		@ echo "$(BLUE)Monitoring.log - Deleted file! $(RST)"

re: fclean all

.PHONY: all clean fclean re