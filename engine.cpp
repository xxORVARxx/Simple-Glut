
#include "Engine.h"
#include <iostream>
#include <assert.h>



// Function Pointer:
void(*the_initialize_func_ptr)() = nullptr;
void(*the_display_resize_func_ptr)(int,int) = nullptr;
void(*the_loop_func_ptr)() = nullptr;



void
ENGINE::Set_the_initialize_function( void(*_func_ptr)() ) {
  the_initialize_func_ptr = _func_ptr;
}

void
ENGINE::Set_the_display_resize_function( void(*_func_ptr)(int,int) ) {
  the_display_resize_func_ptr = _func_ptr;
  glutReshapeFunc( &ENGINE::On_display_resize );
}

void
ENGINE::Set_the_loop_function( void(*_func_ptr)() ) {
  the_loop_func_ptr = _func_ptr;
}



void
ENGINE::Initialize( int* _argc, char** _argv ) {
  glutInit( _argc, _argv );
  glutInitDisplayMode( GLUT_DOUBLE );
  glutInitWindowSize( glutGet( GLUT_SCREEN_WIDTH ) / 2,
		      glutGet( GLUT_SCREEN_HEIGHT ) / 2 );//( 1280, 720 )//( 1920, 1080 );
  glutCreateWindow( "Glut" );
  glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
  glutDisplayFunc( ENGINE::Loop );
}

void
ENGINE::On_display_resize( int _new_width, int _new_height ) {
  /*ASSERT*/assert( the_display_resize_func_ptr != nullptr );
  the_display_resize_func_ptr( _new_width, _new_height );
  glViewport( 0, 0, _new_width, _new_height );
}

void
ENGINE::Loop() {
  glClear( GL_COLOR_BUFFER_BIT );
  /*ASSERT*/assert( the_loop_func_ptr != nullptr );
  the_loop_func_ptr();
  glutSwapBuffers();
}

void
ENGINE::Start() {
  /*ASSERT*/assert( the_initialize_func_ptr != nullptr );
  the_initialize_func_ptr();
  glutMainLoop();
}
