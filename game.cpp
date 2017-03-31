
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
    GAME::the_game.m_triangles.push_back( xx::Make_random_triangle_geometric());  
  }//for

  GAME::the_game.m_test_model.m_geometric = GAME::the_game.m_triangles[0];
  GAME::the_game.m_test_model.m_matrix = xx::Translate({ 0.5f, 0.5f, 0.0f }, xx::Scale({ 5.0f, 5.0f, 0.0f }));
}

void
GAME::On_display_resize( int _new_width, int _new_height ) {
  //std::cout <<"Display Resized To: "<< _new_width <<'x'<< _new_height <<".\n";
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

glm::vec2
GAME::Display::Get_pixels() {
  return m_pixels;
}

glm::vec2
GAME::Display::Get_size() {
  return m_size;
}

glm::vec2
GAME::Display::Get_ratio() {
  return m_ratio;
}



void
GAME::Game::Logic() {
}

void
Draw_triangle( xx::Triangle_geometric& _t, glm::vec2 _scale,  glm::vec2 _move );

void
Draw_triangle( xx::Triangle_model& _model );

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

  
  glColor3f( 1.0f, 0.0f, 0.0f );
  Draw_triangle( GAME::the_game.m_test_model );
  
  
  glColor3f( 1.0f, 1.0f, 1.0f );
  for( unsigned int i = 0 ; i < m_triangles.size() ; ++i ) {
    Draw_triangle( m_triangles[i],
		   GAME::the_display.Get_ratio(),
		   GAME::the_display.Get_ratio() * glm::vec2( GAME::the_display.m_tiles[i] ));
  }
  
  glEnd();
}



void
Draw_triangle( xx::Triangle_geometric& _t, glm::vec2 _scale,  glm::vec2 _move ) {
  glVertex2f((( _t.a.x * _scale.x ) + _move.x ), (( _t.a.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.b.x * _scale.x ) + _move.x ), (( _t.b.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.b.x * _scale.x ) + _move.x ), (( _t.b.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.c.x * _scale.x ) + _move.x ), (( _t.c.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.c.x * _scale.x ) + _move.x ), (( _t.c.y * _scale.y ) + _move.y ));
  glVertex2f((( _t.a.x * _scale.x ) + _move.x ), (( _t.a.y * _scale.y ) + _move.y ));
}



void
Draw_triangle( xx::Triangle_model& _model ) {
  glm::vec3 a = _model.m_geometric.a * _model.m_matrix;
  glm::vec3 b = _model.m_geometric.b * _model.m_matrix;
  glm::vec3 c = _model.m_geometric.c * _model.m_matrix;
  glVertex2f( a.x, a.y);
  glVertex2f( b.x, b.y);
  glVertex2f( b.x, b.y);
  glVertex2f( c.x, c.y);
  glVertex2f( c.x, c.y);
  glVertex2f( a.x, a.y); 
}
