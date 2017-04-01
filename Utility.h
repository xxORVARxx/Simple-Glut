
#ifndef UTILITY_H
#define UTILITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <chrono>
#include <random>


/*** *** *** RANDOM *** *** ***/
namespace xx {
  class Random {
  public:
    Random( int _seed = 0 );
    void Set_distribution( double _min, double _max );
    double operator()();
    int Get_seed();
    
  private:
    int m_seed;
    std::mt19937 m_engine;
    std::uniform_real_distribution< double >* m_distribution_ptr;
  } extern the_random;
}//xx



/*** *** *** GLM *** *** ***/
std::ostream&
operator<< ( std::ostream& _out, const glm::vec3& _source );

std::ostream&
operator<< ( std::ostream& _out, const glm::mat3& _source );

namespace xx {
  glm::vec3
  From2to3_0( glm::vec2 _v );
  
  glm::vec3
  From2to3_1( glm::vec2 _v );
  
  glm::mat3
  Translate( glm::vec3 const& _v, glm::mat3 const& _m = glm::mat3());
  
  glm::mat3
  Scale( glm::vec3 const& _v, glm::mat3 const& _m = glm::mat3());
  
  void
  Set_translation( glm::vec3 const& _v, glm::mat3& _m );

  void
  Set_Scale( glm::vec3 const& _v, glm::mat3& _m );
}//xx



/*** *** *** TILES *** *** ***/
namespace xx {
  class Tiles {
  public:
    void Make_tiles( int _row, int _col );
    unsigned int Size();
    glm::vec3 operator[]( unsigned int _at );
    
    int m_rows;
    int m_cols;
    float m_row_size;
    float m_col_size;
    std::vector< glm::vec3 > m_tiles;
  };
}//xx



/*** *** *** MODEL *** *** ***/
namespace xx {
  class Model {
  public:
    glm::vec3 Get_position( unsigned int _at );
    
    std::vector< glm::mat3 > m_matrices;
    std::vector< glm::vec3 > m_geometric;
  };
}//xx



#endif
