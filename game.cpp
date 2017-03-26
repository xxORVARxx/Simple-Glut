
#include "Game.h"
#include <iostream>



namespace GAME {
  Display the_display;
  Game the_game;
}//GAME



void
GAME::Initialize() {
  unsigned int num = 10 ;
  xx::the_random.Set_distribution( -1.0d / 10.0d, 1.0d / 10.0d );
  GAME::the_display.m_tiles.Make_tiles( 10, 10 );
  GAME::the_game.m_triangles.reserve( GAME::the_display.m_tiles.Size());
  for( unsigned int i = 0 ; i < num * num ; ++i ) {
    GAME::the_game.m_triangles.push_back( xx::Make_random_triangle());
  }//for
}

void
GAME::On_display_resize( int _new_width, int _new_height ) {
  glViewport( 0, 0, _new_width, _new_height );
  std::cout <<"Display Resized To: "<< _new_width <<'x'<< _new_height <<".\n";
  if( GAME::the_display.m_pixels_original.x < 0.0f )
    GAME::the_display.m_pixels_original.x = _new_width;
  if( GAME::the_display.m_pixels_original.y < 0.0f )
    GAME::the_display.m_pixels_original.y = _new_height;
  GAME::the_display.m_pixels.x = _new_width;
  GAME::the_display.m_pixels.y = _new_height;
  if( GAME::the_display.m_pixels.x > GAME::the_display.m_pixels.y )
    GAME::the_display.m_ratio.x = ( GAME::the_display.m_pixels.y /
					GAME::the_display.m_pixels.x );
  else
    GAME::the_display.m_ratio.y= ( GAME::the_display.m_pixels.x /
					 GAME::the_display.m_pixels.y );
}

void
GAME::Loop() {
  GAME::the_game.Logic();
  GAME::the_game.Draw();
}



GAME::Display::Display() :
  m_pixels_original( -1.0f, -1.0f ),
  m_pixels( 0.0f, 0.0f ),
  m_size( 2.0f, 2.0f ),
  m_ratio( 1.0f, 1.0f ) {
}



void
GAME::Game::Logic() {

}


void
Draw_triangle( xx::Triangle& _t, glm::vec2 _scale,  glm::vec2 _move ) {
  glVertex2f((( _t.a.x * _scale.x ) + _move.x ), (( _t.a.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.b.x * _scale.x ) + _move.x ), (( _t.b.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.b.x * _scale.x ) + _move.x ), (( _t.b.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.c.x * _scale.x ) + _move.x ), (( _t.c.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.c.x * _scale.x ) + _move.x ), (( _t.c.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.a.x * _scale.x ) + _move.x ), (( _t.a.y * _scale.y ) + _move.y ));
}


void
GAME::Game::Draw() {
  glBegin( GL_LINES );
  
  { // Cross:
    glColor3f( 1.0f, 1.0f, 0.0f );
    glVertex2f( 0.0f, -0.1f );
    glVertex2f( 0.0f, 0.1f );
    glVertex2f( -0.1f, 0.0f );
    glVertex2f( 0.1f, 0.0f );
  }
  { // Line
    glColor3f( 0.0f, 0.0f, 1.0f );
    glVertex2f( -1.0f, -1.0f );
    glVertex2f( 0.0f, 0.0f );
  }
  
  glColor3f( 1.0f, 1.0f, 1.0f );
  for( unsigned int i = 0 ; i < m_triangles.size() ; ++i ) {
    Draw_triangle( m_triangles[i],
		   GAME::the_display.m_ratio,
		   GAME::the_display.m_tiles[i] * GAME::the_display.m_ratio );
  }
  
  glEnd();
}

