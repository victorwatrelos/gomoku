# include <chrono>
# include <iostream>
# include "Board.hpp"
# include "display/StdOutDisplay.hpp"
# include "engine/GameLoop.hpp"

int		main()
{
//	GameLoop	game;

//	game.launchGame();
  
  VHeuristic	h;
  h.display = true;
  Board	b;

  b.setMove(0 * GRID_LENGTH, Board::Point::WHITE);
  b.setMove(1 * GRID_LENGTH, Board::Point::WHITE);
  b.setMove(2 * GRID_LENGTH, Board::Point::BLACK);
  b.setMove(3 * GRID_LENGTH, Board::Point::BLACK);
  b.setMove(4 * GRID_LENGTH, Board::Point::BLACK);
  b.setMove(5 * GRID_LENGTH, Board::Point::BLACK);
  b.setMove(6 * GRID_LENGTH, Board::Point::WHITE);
  StdOutDisplay	disp;
  disp.displayBoard(b);
  h.eval(&b, Board::Point::BLACK, true);
	
	return (0);
}
