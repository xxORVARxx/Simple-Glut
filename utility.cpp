
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



std::ostream&
operator<< ( std::ostream& _out, const glm::vec3& _source ) {
  _out <<"("<< _source.x <<", "<< _source.y <<", "<< _source.z <<") ";
  return _out;
}

std::ostream&
operator<< ( std::ostream& _out, const glm::mat3& _source ) {
  _out <<"|"<< _source[0].x <<", "<< _source[0].y <<", "<< _source[0].z <<"|\n"
       <<"|"<< _source[1].x <<", "<< _source[1].y <<", "<< _source[1].z <<"|\n"
       <<"|"<< _source[2].x <<", "<< _source[2].y <<", "<< _source[2].z <<"| ";
  return _out;
}

glm::mat3
xx::Translate( const glm::vec3& _v, const glm::mat3& _m ) {
  return glm::mat3( _m[0].x, _m[0].y, _m[0].z + _v.x,
		    _m[1].x, _m[1].y, _m[1].z + _v.y,
		    _m[2].x, _m[2].y, _m[2].z );
}
  
glm::mat3
xx::Scale( const glm::vec3& _v, const glm::mat3& _m ) {
  return glm::mat3( _m[0].x * _v.x, _m[0].y,        _m[0].z,
		    _m[1].x,        _m[1].y * _v.y, _m[1].z,
		    _m[2].x,        _m[2].y,        _m[2].z );
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
	                  row_begin + ( m_row_size * i ), 0.0f });
    }//for
    ++i;
    for( int j = m_cols ; j >= 1 ; --j ) {
      m_tiles.push_back({ col_begin + ( m_col_size * j ),
	                  row_begin + ( m_row_size * i ), 0.0f });
    }//for
  }//for
}

unsigned int
xx::Tiles::Size() {
  return m_tiles.size();
}

glm::vec3
xx::Tiles::operator[]( unsigned int _at ) {
  return m_tiles.at( _at );
}



namespace xx {
  std::ostream& operator<< ( std::ostream& _out, const xx::Triangle_geometric& _source ) {
    std::cout <<"a( "<< _source.a.x <<", "<< _source.a.y <<" ), "
	      <<"b( "<< _source.b.x <<", "<< _source.b.y <<" ), "
	      <<"c( "<< _source.c.x <<", "<< _source.c.y <<" ) ";
    return _out;
  }
}//xx



xx::Triangle_geometric
xx::Make_random_triangle_geometric() {
  xx::Triangle_geometric t; 
  t.a.x = xx::the_random();
  t.a.y = xx::the_random();
  t.a.z = 1.0f;;
  t.b.x = xx::the_random();
  t.b.y = xx::the_random();
  t.b.z = 1.0f;;
  t.c.x = xx::the_random();
  t.c.y = xx::the_random();
  t.c.z = 1.0f;;
  return t;
}

void
xx::Move_triangle_geometric( xx::Triangle_geometric& _t, const glm::vec3& _vec ) {
  _t.a += _vec;
  _t.b += _vec;
  _t.c += _vec;
  _t.pos += _vec;
}
