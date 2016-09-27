CC= clang++
FLAGS=-Wall -Wextra -Werror -std=c++11 -g
NAME= gomoku

SRC= main.cpp \
	 players/AbstractPlayer.cpp \
	 players/STDINPlayer.cpp \
	 display/AbstractDisplay.cpp \
	 display/StdOutDisplay.cpp \
	 engine/GameLoop.cpp \
	 ai/AI.cpp \
	 ai/State.cpp \
	 heuristics/BadHeuristic.cpp \
	 Board.cpp

OBJ= $(SRC:.cpp=.o)

LIB=

FRWK= 
.PHONY: clean fclean re all
.SILENT:
all:$(NAME) 

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB) $(FRWK) $(INC) $(FLAGS)
		echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME) \033[0mDONE!"

%.o: %.cpp
		echo "\t\xF0\x9F\x94\xA7   Building \033[34m $@ \033[0m" 
		$(CC) -c $(FLAGS) $(INC) -o $@ $<

clean:
		echo "\t\xF0\x9F\x92\xA3   Cleaning"
		rm -rf $(OBJ)

fclean: clean
		echo "\t\xF0\x9F\x9A\xBD   Full Clean"
		rm -rf $(NAME)

re: fclean all
