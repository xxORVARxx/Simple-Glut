
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
  unsigned int num = 10 ;
  xx::the_random.Set_distribution( -1.0d / 10.0d, 1.0d / 10.0d );
  GAME::the_game.m_triangles.reserve( num * num );
  for( unsigned int i = 0 ; i < num * num ; ++i )
    GAME::the_game.m_triangles.push_back( xx::Make_random_triangle());
  
  for( unsigned int i = 0, col = 0 ; col < num ; ++col ) {
    for( unsigned int row = 0 ; row < num ; ++row, ++i ) {
      glm::vec2 vec;
      vec.x = (( 2.0f / num ) * row ) -1;
      vec.y = (( 2.0f / num ) * col ) -1;
      xx::Move_triangle( GAME::the_game.m_triangles[i], vec );   
    }//for
  }//for


  
  for( unsigned int i = 0 ; i < num * num ; ++i ) {
    GAME::the_game.m_x.push_back( xx::Make_x());
  }
  
  for( unsigned int i = 0, col = 0 ; col < num ; ++col ) {
    for( unsigned int row = 0 ; row < num ; ++row, ++i ) {
      glm::vec2 vec;
      vec.x = (( 2.0f / num ) * row ) -1;
      vec.y = (( 2.0f / num ) * col ) -1;  
      xx::Move_x( GAME::the_game.m_x[i], vec );
    }//for
  }//for
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
  
  glColor3f( 1.0f, 0.0f, 1.0f );
  for( unsigned int i = 0 ; i < m_x.size() ; ++i ) {
    glVertex2f( m_x[i].a.x, m_x[i].a.y );
    glVertex2f( m_x[i].b.x, m_x[i].b.y );

    glVertex2f( m_x[i].c.x, m_x[i].c.y );
    glVertex2f( m_x[i].d.x, m_x[i].d.y );
  }

  glColor3f( 1.0f, 1.0f, 0.0f );
  glVertex2f( 0.0, -0.1 );
  glVertex2f( 0.0, 0.1 );
  
  glVertex2f( -0.1, 0.0 );
  glVertex2f( 0.1, 0.0 );
  
  glEnd();
}

