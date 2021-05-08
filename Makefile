NAME = prac

LIBFT = funcs

SRC = root.c

SRC_OBJECTS = $(patsubst %.c,%.o,$(SRC))

FLAGS = -Wall -Wextra -Werror -g

all: MKLIB $(NAME).a

MKLIB:
	make -C $(LIBFT)
$(NAME).a: $(LIBFT)/$(LIBFT).a $(SRC_OBJECTS)
	cp $(LIBFT)/$(LIBFT).a ./$(NAME).a
	ar rcs $(NAME).a $(SRC_OBJECTS)

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@
	@echo "$@ added"

clean:
	@/bin/rm -rf $(SRC_OBJECTS)
	make -C $(LIBFT) clean
	@echo "All objects removed"

fclean: clean
	@rm $(NAME).a
	make -C $(LIBFT) fclean
	@echo "$(NAME) removed"

re:
	make -C $(LIBFT) fclean
	make fclean
	make all

bonus: all
.PHONY: all clean fclean re