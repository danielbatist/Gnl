CC = cc 

CFLAGS = -Wall -Wextra -Werror

NAME = get_next_line.a

SRC = get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

.c.o: 
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	ar rcs $@ $(OBJ)

clean: 
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean
