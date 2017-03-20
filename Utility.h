
#ifndef UTILITY_H
#define UTILITY_H

#include <glm/glm.hpp>
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



namespace xx {
  struct Triangle {
    friend std::ostream& operator<< ( std::ostream& _out, const xx::Triangle& _source );
    glm::vec2 a;
    glm::vec2 b;
    glm::vec2 c;
  };
}//xx



namespace xx {
  struct X {
    glm::vec2 a;
    glm::vec2 b;
    glm::vec2 c;
    glm::vec2 d;
  };
}//xx



namespace xx {
  xx::Triangle Make_random_triangle();
  void Move_triangle( xx::Triangle& _t, const glm::vec2& _vec );

  xx::X Make_x();
  void Move_x( xx::X& _x, const glm::vec2& _vec );
}//xx



#endif
