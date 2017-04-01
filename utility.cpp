
#include "Utility.h"
#include "Game.h"



namespace xx {
  Random the_random;
}//xx



/*** *** ***  RANDOM *** *** ***/
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



/*** *** *** GLM *** *** ***/
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

glm::vec3
xx::From2to3_0( glm::vec2 _v ) {
  return{ _v.x, _v.y, 0.0f };
}
  
glm::vec3
xx::From2to3_1( glm::vec2 _v ) {
  return{ _v.x, _v.y, 1.0f };
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
xx::Set_translation( glm::vec3 const& _v, glm::mat3& _m ) {
  _m[0].z = _v.x;
  _m[1].z = _v.y;
}

void
xx::Set_Scale( glm::vec3 const& _v, glm::mat3& _m ) {
  _m[0].x = _v.x;
  _m[1].y = _v.y;
}



/*** *** *** TILES *** *** ***/
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
	                  row_begin + ( m_row_size * i ), 1.0f });
    }//for
    ++i;
    for( int j = m_cols ; j >= 1 ; --j ) {
      m_tiles.push_back({ col_begin + ( m_col_size * j ),
	                  row_begin + ( m_row_size * i ), 1.0f });
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



/*** *** *** MODEL *** *** ***/
glm::vec3
xx::Model::Get_position( unsigned int _at ) {
  return{ m_matrices.at( _at )[0].z, m_matrices.at( _at )[1].z, m_matrices.at( _at )[2].z };
}
