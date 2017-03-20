
#include "Utility.h"



namespace xx {
  Random the_random;
}//xx



xx::Random::Random( int _seed ) :
  m_seed(_seed),
  m_distribution_ptr( nullptr ) {
  if( m_seed == 0 ) 
    m_seed = std::chrono::system_clock::now().time_since_epoch().count(); 
  m_engine.seed( m_seed );
}

void xx::Random::Set_distribution( double _min, double _max ) {
  if( m_distribution_ptr != nullptr )
    delete m_distribution_ptr;
  m_distribution_ptr = new std::uniform_real_distribution< double >( _min, _max );
}

double xx::Random::operator()() {
  if( m_distribution_ptr != nullptr )
    return (*m_distribution_ptr)( m_engine );
  return 0.0f;
}

int xx::Random::Get_seed() {
  return m_seed;
}



namespace xx {
  std::ostream& operator<< ( std::ostream& _out, const xx::Triangle& _source ) {
    std::cout <<"a( "<< _source.a.x <<", "<< _source.a.y <<" ), "
	      <<"b( "<< _source.b.x <<", "<< _source.b.y <<" ), "
	      <<"c( "<< _source.c.x <<", "<< _source.c.y <<" ) ";
    return _out;
  }
}//xx



xx::Triangle xx::Make_random_triangle() {
  xx::Triangle t; 
  t.a.x = xx::the_random();
  t.a.y = xx::the_random();
  t.b.x = xx::the_random();
  t.b.y = xx::the_random();
  t.c.x = xx::the_random();
  t.c.y = xx::the_random();
  return t;
}

void xx::Move_triangle( xx::Triangle& _t, const glm::vec2& _vec ) {
  _t.a += _vec;
  _t.b += _vec;
  _t.c += _vec;
}



xx::X xx::Make_x() {
  xx::X x;
  x.a.x = -0.5;
  x.a.y = -0.5;
  x.b.x = 0.5;
  x.b.y = 0.5;
  x.c.x = -0.5;
  x.c.y = 0.5;
  x.d.x = 0.5;
  x.d.y = -0.5;
  x.a /= 10.0f ;
  x.b /= 10.0f ;
  x.c /= 10.0f ;
  x.d /= 10.0f ;  
  return x;
}

void xx::Move_x( xx::X& _x, const glm::vec2& _vec ) {
  _x.a += _vec;
  _x.b += _vec;
  _x.c += _vec;
  _x.d += _vec;
}
