NAME = funcs.a

SRC = val_f1.asm val_f2.asm val_f3.asm der1_f1.asm der1_f2.asm \
		der1_f3.asm der2_f1.asm der2_f2.asm der2_f3.asm

SRC_OBJECTS = $(patsubst %.asm,%.o,$(SRC))

HEADERS = ../headers

FLAGS = -f elf

all: $(NAME)

$(NAME): $(SRC_OBJECTS)
	@ar rc $(NAME) $(SRC_OBJECTS)
	@ranlib $(NAME)
	@echo "$(NAME) generated"

%.o: %.asm $(HEADERS)
	@nasm $(FLAGS) $< -o $@
	@echo "$@ added"

clean:
	@rm -f $(SRC_OBJECTS)
	@echo "All objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all