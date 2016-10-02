# include <chrono>
# include <iostream>
# include "Board.hpp"
# include "display/StdOutDisplay.hpp"
# include "engine/GameLoop.hpp"

int		main()
{
	GameLoop	game;

	game.launchGame();
  
  	/*
  VHeuristic	h;
  h.display = true;
  Board	b;


  int	line = 19 * 11;
  b.setMove(12 + line, Board::Point::EMPTY);
  b.setMove(13 + line, Board::Point::WHITE);
  b.setMove(14 + line, Board::Point::BLACK);
  b.setMove(15 + line, Board::Point::BLACK);
  b.setMove(16 + line, Board::Point::BLACK);
  b.setMove(17 + line, Board::Point::BLACK);
  b.setMove(18 + line, Board::Point::BLACK);
  StdOutDisplay	disp;
  disp.displayBoard(b);
  h.eval(&b, Board::Point::BLACK, true);
  */
	
	return (0);
}
