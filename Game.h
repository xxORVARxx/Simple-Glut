
#ifndef GAME_H
#define GAME_H

#include "Engine.h"
#include "Utility.h"
#include <vector>



namespace GAME {
  void Display();
  void Initialize();
}//GAME



namespace GAME {
  class Game {
  public:
    void Logic();
    void Draw();

    std::vector< xx::Triangle > m_triangles;
    std::vector< xx::X > m_x;
  } extern the_game;
}//GAME



#endif
