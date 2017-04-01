
#include "Game.h"
#include <iostream>



namespace GAME {
  Display the_display;
  Game the_game;
}//GAME



/*** *** *** FUNCTIONS *** *** ***/
void
GAME::Initialize() {
  unsigned int num = 10 ;
  // Make Models:
  GAME::the_game.m_triangles.reserve(( num * num ) + 1 );
  for( unsigned int i = 0 ; i < num * num ; ++i )
    GAME::the_game.m_triangles.push_back( xx::Model());
  // Give The Models Some Geometric:
  xx::the_random.Set_distribution( -1.0d, 1.0d );
  for( unsigned int i = 0 ; i < GAME::the_game.m_triangles.size() ; ++i ) {
    GAME::the_game.m_triangles[i].m_geometric.push_back({ xx::the_random(), xx::the_random(), 1.0f });
    GAME::the_game.m_triangles[i].m_geometric.push_back({ xx::the_random(), xx::the_random(), 1.0f });
    GAME::the_game.m_triangles[i].m_geometric.push_back({ xx::the_random(), xx::the_random(), 1.0f });
  }//for
  // Make Tiles To Organize The Models On The Screen:
  GAME::the_game.m_tiles.Make_tiles( num, num );
  for( unsigned int i = 0 ; i < GAME::the_game.m_triangles.size() ; ++i ) {
    glm::mat3 m = xx::Scale({ 1.0f / num, 1.0f / num, 1.0f }); // Scale Model.
    m = xx::Translate( GAME::the_game.m_tiles[i], m ); // Move Model.
    GAME::the_game.m_triangles[i].m_matrices.push_back( m );  
  }//for
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



/*** *** *** DISPLAY *** *** ***/
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



/*** *** *** GAME *** *** ***/
void
GAME::Game::Logic() {
}

void
Draw_model( xx::Model& _model, glm::mat3 _display );

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

  glColor3f( 1.0f, 0.0f, 1.0f );
  glm::mat3 display_mat = xx::Scale( xx::From2to3_1( GAME::the_display.Get_ratio()));
  for( unsigned int i = 0 ; i < GAME::the_game.m_triangles.size() ; ++i )
    Draw_model( GAME::the_game.m_triangles[i], display_mat );

  glEnd();
}

void
Draw_model( xx::Model& _model, glm::mat3 _display ) {
  if( _model.m_matrices.empty())
    return;
  if( _model.m_geometric.size() > 2 ) {
    for( unsigned int i = 0 ; i < _model.m_matrices.size() ; ++i ) {
      glm::vec3 v[3];
      bool curr = 0;
      v[curr] = _model.m_geometric[0] * _model.m_matrices[i] * _display;
      v[2] = v[curr]; // Starting Point, (Saveing It).
    
      for( long int j = 0 ; j + 1 < _model.m_geometric.size() ; ++j ) {
	curr = !curr; // Swamp Current Point.
	v[curr] = _model.m_geometric[j+1] * _model.m_matrices[i] * _display;	

	glVertex2f( v[!curr].x, v[!curr].y );
	glVertex2f( v[curr].x, v[curr].y );	
      }//for
      // Closing the loop:
      glVertex2f( v[curr].x, v[curr].y );
      glVertex2f( v[2].x, v[2].y ); // Starting Point.	
    }//for
  }
  else if( _model.m_geometric.size() == 2 ) {
    for( unsigned int i = 0 ; i < _model.m_matrices.size() ; ++i ) {
      glm::vec3 v1 = _model.m_geometric[0] * _model.m_matrices[i] * _display;
      glm::vec3 v2 = _model.m_geometric[1] * _model.m_matrices[i] * _display;
      glVertex2f( v1.x, v1.y );
      glVertex2f( v2.x, v2.y );
    }//for
  }
}
