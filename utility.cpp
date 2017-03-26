
#include "Utility.h"
#include "Game.h"



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

void
xx::Random::Set_distribution( double _min, double _max ) {
  if( m_distribution_ptr != nullptr )
    delete m_distribution_ptr;
  m_distribution_ptr = new std::uniform_real_distribution< double >( _min, _max );
}

double
xx::Random::operator()() {
  if( m_distribution_ptr != nullptr )
    return (*m_distribution_ptr)( m_engine );
  return 0.0f;
}

int
xx::Random::Get_seed() {
  return m_seed;
}



void
xx::Tiles::Make_tiles( int _row, int _col ) {
  m_rows = _row;
  m_cols = _col;
  m_row_size = 2.0f / m_rows;
  m_col_size = 2.0f / m_cols;
  m_tiles.reserve( m_rows * m_cols );
  float row_begin = ( -1.0f - ( m_row_size / 2 ));
  float col_begin = ( -1.0f - ( m_col_size / 2 ));  
  for( int i = 1 ; i < m_rows ; ++i ) {	
    for( int j = 1 ; j <= m_cols ; ++j ) {
      m_tiles.push_back({ col_begin + ( m_col_size * j ),
	    row_begin + ( m_row_size * i ) });
    }//for
    ++i;
    for( int j = m_cols ; j >= 1 ; --j ) {
      m_tiles.push_back({ col_begin + ( m_col_size * j ),
	    row_begin + ( m_row_size * i ) });
    }//for
  }//for
}

unsigned int
xx::Tiles::Size() {
  return m_tiles.size();
}

glm::vec2
xx::Tiles::operator[]( unsigned int _at ) {
  return m_tiles.at( _at );
}



namespace xx {
  std::ostream& operator<< ( std::ostream& _out, const xx::Triangle& _source ) {
    std::cout <<"a( "<< _source.a.x <<", "<< _source.a.y <<" ), "
	      <<"b( "<< _source.b.x <<", "<< _source.b.y <<" ), "
	      <<"c( "<< _source.c.x <<", "<< _source.c.y <<" ) ";
    return _out;
  }
}//xx



xx::Triangle
xx::Make_random_triangle() {
  xx::Triangle t; 
  t.a.x = xx::the_random();
  t.a.y = xx::the_random();
  t.b.x = xx::the_random();
  t.b.y = xx::the_random();
  t.c.x = xx::the_random();
  t.c.y = xx::the_random();
  return t;
}

void
xx::Move_triangle( xx::Triangle& _t, const glm::vec2& _vec ) {
  _t.a += _vec;
  _t.b += _vec;
  _t.c += _vec;
}
