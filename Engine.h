 
#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glut.h>
#include <glm/glm.hpp>



namespace ENGINE {
  void Set_display_function( void(*_func_ptr)() );
  void Set_Initialize_function( void(*_func_ptr)() );

  void Initialize( int* _argc, char** _argv );
  void Display();
  void Start();
}//ENGINE



#endif
