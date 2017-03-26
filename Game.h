
#ifndef GAME_H
#define GAME_H

#include "Engine.h"
#include "Utility.h"
#include <vector>



namespace GAME {
  void Initialize();
  void On_display_resize( int _new_width, int _new_height );
  void Loop();
}//GAME



namespace GAME {
  struct Display {
    Display();
    
    glm::vec2 m_pixels_original;
    glm::vec2 m_pixels;
    glm::vec2 m_size;
    glm::vec2 m_ratio;
    xx::Tiles m_tiles;
  } extern the_display;
}//GAME



namespace GAME {
  class Game {
  public:
    void Logic();
    void Draw();

    std::vector< xx::Triangle > m_triangles;
  } extern the_game;
}//GAME



#endif
