CC := c++

CFLAGS := -Wall -Wextra -Werror -g -MMD -MP -I include/ -std=c++98

D_OBJ := .obj/

F_SRC := main.cpp\
		 BitcoinExchange.cpp

D_SRC := src/

SRC := $(addprefix $(D_SRC), $(F_SRC))

OBJ := $(subst $(D_SRC), $(D_OBJ), $(SRC:.cpp=.o))

DEPS := $(OBJ:.o=.d)

NAME := btc

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(D_OBJ)%.o : $(D_SRC)%.cpp
	@mkdir -p $(D_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean :
	rm -rf $(D_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all