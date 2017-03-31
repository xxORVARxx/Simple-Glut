
#ifndef UTILITY_H
#define UTILITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <chrono>
#include <random>



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



std::ostream&
operator<< ( std::ostream& _out, const glm::vec3& _source );

std::ostream&
operator<< ( std::ostream& _out, const glm::mat3& _source );

namespace xx {
  glm::mat3
  Translate( glm::vec3 const& _v, glm::mat3 const& _m = glm::mat3());
  
  glm::mat3
  Scale( glm::vec3 const& _v, glm::mat3 const& _m = glm::mat3());  
}//xx



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



namespace xx {
  struct Triangle_geometric {
    friend std::ostream& operator<< ( std::ostream& _out, const xx::Triangle_geometric& _source );
    
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;
    glm::vec3 pos;
  };
}//xx



namespace xx {
  struct Triangle_model {
    glm::mat3 m_matrix;
    xx::Triangle_geometric m_geometric;
  };
}//xx



namespace xx {
  xx::Triangle_geometric Make_random_triangle_geometric();
  void Move_triangle_geometric( xx::Triangle_geometric& _t, const glm::vec3& _vec );
}//xx



#endif
