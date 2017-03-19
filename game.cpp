
#include "Game.h"
#include <iostream>



namespace GAME {
  Game the_game;
}//GAME



void GAME::Display() {
  GAME::the_game.Logic();
  GAME::the_game.Draw();
}

void GAME::Initialize() {
  xx::the_random.Set_distribution( -1.0d, 1.0d );
  GAME::the_game.m_triangles.reserve(100);
  for( unsigned int i = 0 ; i < 10 ; ++i )
    GAME::the_game.m_triangles.push_back( xx::Make_random_Triangle());
}



void GAME::Game::Logic() {

}

void GAME::Game::Draw() {
  glBegin( GL_LINES );   
  glColor3f( 1.0f, 1.0f, 1.0f );
  for( unsigned int i = 0 ; i < m_triangles.size() ; ++i ) {

    glVertex2f( m_triangles[i].a.x, m_triangles[i].a.y );
    glVertex2f( m_triangles[i].b.x, m_triangles[i].b.y );

    glVertex2f( m_triangles[i].b.x, m_triangles[i].b.y );
    glVertex2f( m_triangles[i].c.x, m_triangles[i].c.y );

    glVertex2f( m_triangles[i].c.x, m_triangles[i].c.y );
    glVertex2f( m_triangles[i].a.x, m_triangles[i].a.y );	  
    
  }
  glEnd();
}

