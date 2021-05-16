NAME = proj

LIBPATH = asmsrcs

LIB = asmsrcs/funcs.a

SRC = srcs/integral.c srcs/root.c srcs/options.c srcs/main.c

SRC_OBJECTS = $(patsubst %.c,%.o,$(SRC))

HEADERS = headers/

FLAGS = -Wall -Wextra -Werror -g -m32 -I $(HEADERS)

all: MKLIB $(SRC_OBJECTS)
	@gcc $(FLAGS) -o $(NAME) $(SRC_OBJECTS) $(LIB) -lm

MKLIB:
	make -C $(LIBPATH)

%.o: %.c $(HEADERS)
	@gcc $(FLAGS) -c $< -o $@ -lm
	@echo "$@ added"

clean:
	@rm -f $(SRC_OBJECTS)
	make -C $(LIBPATH) clean
	@echo "All objects removed"

fclean: clean
	@rm -f $(NAME)
	make -C $(LIBPATH) fclean
	@echo "$(NAME) removed"

re:
	make -C $(LIBPATH) fclean
	make fclean
	make all

.PHONY: all clean fclean re