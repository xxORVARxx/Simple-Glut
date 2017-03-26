/*  To Compile Use:
 *    g++ -std=c++11 -o test.bin  *.cpp  -lglut -lGLU -lGL
 */

#include "Game.h"
#include <iostream>



int
main( int argc, char** argv ) {
  ENGINE::Initialize( &argc, argv );
  ENGINE::Set_the_initialize_function( &GAME::Initialize );
  ENGINE::Set_the_display_resize_function( &GAME::On_display_resize );
  ENGINE::Set_the_loop_function( &GAME::Loop );
  ENGINE::Start();
  return 0;
}
