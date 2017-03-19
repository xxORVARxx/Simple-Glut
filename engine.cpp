
#include "Engine.h"
#include <iostream>



// Function Pointer To a Draw/Display Function To Be Used:
void(*display_func_ptr)() = nullptr;
void(*Initialize_func_ptr)() = nullptr;



void ENGINE::Set_display_function( void(*_func_ptr)() ) {
  display_func_ptr = _func_ptr;
}

void ENGINE::Set_Initialize_function( void(*_func_ptr)() ) {
  Initialize_func_ptr = _func_ptr;
}



void ENGINE::Initialize( int* _argc, char** _argv ) {
  glutInit( _argc, _argv );
  glutInitDisplayMode( GLUT_DOUBLE );
  glutInitWindowSize( 1080, 1080 );//( 1280, 720 )//( 1920, 1080 );
  glutCreateWindow( "Glut" );
  glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
  glutDisplayFunc( ENGINE::Display );
}

void ENGINE::Display() {
  glClear( GL_COLOR_BUFFER_BIT );
  if( display_func_ptr != nullptr )
    display_func_ptr();
  glutSwapBuffers();
}

void ENGINE::Start() {
  if( Initialize_func_ptr != nullptr )
    Initialize_func_ptr();
  glutMainLoop();
}
