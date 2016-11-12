CC= clang++
FLAGS=-Wall -Wextra  -std=c++14 -g
NAME= gomoku_test

SRC= main.cpp \
	 loadBoard.cpp \
	 testCheckForceMove.cpp \
	 testAi.cpp \
	 ../display/AbstractDisplay.cpp \
	 ../display/StdOutDisplay.cpp \
	 ../heuristics/MHeuristic.cpp \
	 ../heuristics/LineData.cpp \
	 ../utilities/BrowseBoard.cpp \
	 ../utilities/AbstractLineData.cpp \
	 ../utilities/HashUtilities.cpp \
	 ../utilities/BoardUtilities.cpp \
	 ../utilities/CheckForceMove.cpp \
	 ../players/AbstractPlayer.cpp \
	 ../players/AIPlayer.cpp \
	 ../ai/AI.cpp \
	 ../Board.cpp

	 #utilities/CheckForceMove.cpp \

OBJ= $(SRC:.cpp=.o)

LIB=
INC=-isystem $(HOME)/.brew/include/

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
