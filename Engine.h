 
#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glut.h>
#include <glm/glm.hpp>



namespace ENGINE {
  void Set_the_initialize_function( void(*_func_ptr)() );
  void Set_the_display_resize_function( void(*_func_ptr)(int,int) );  
  void Set_the_loop_function( void(*_func_ptr)() );

  void Initialize( int* _argc, char** _argv );
  void Loop();
  void Start();
}//ENGINE



#endif
