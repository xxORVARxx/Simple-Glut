
/*  To Compile Use:
 *    g++ -std=c++11 -o test.bin  *.cpp  -lglut -lGLU -lGL
 */

#include "Game.h"
#include <iostream>



int main( int argc, char** argv ) {
  ENGINE::Initialize( &argc, argv );
  ENGINE::Set_display_function( &GAME::Display );
  ENGINE::Set_Initialize_function( &GAME::Initialize );
  ENGINE::Start();
  return 0;
}
