#include "GLCircleRenderer2D.h"

GLCircleRenderer2D::GLCircleRenderer2D( const unsigned num_points_single_half )
: m_x_crds( num_points_single_half )
, m_y_crds( num_points_single_half )
{
  assert( num_points_single_half >= 3 );
  // Sample the circle at equal intervals
  const GLdouble dtheta{ MathDefines::PI<GLdouble>() / GLdouble( num_points_single_half - 1 ) };
  m_x_crds( 0 ) = 0.0;
  m_x_crds( num_points_single_half - 1 ) = MathDefines::PI<GLdouble>();
  for( unsigned pnt_num = 1; pnt_num < num_points_single_half - 1; ++pnt_num )
  {
    m_x_crds( pnt_num ) = pnt_num * dtheta;
  }
  m_y_crds = m_x_crds;
  m_x_crds = m_x_crds.array().cos();
  m_y_crds = m_y_crds.array().sin();
}

void GLCircleRenderer2D::renderCircle( const Eigen::Matrix<GLdouble,3,1>& color ) const
{
  glPushAttrib( GL_COLOR );

  // Draw the first half of the circle
  glColor3d( color.x(), color.y(), color.z() );
  glBegin( GL_POLYGON );
  for( int pnt_num = 0; pnt_num < m_x_crds.size(); ++pnt_num )
  {
    glVertex2d( m_x_crds( pnt_num ), m_y_crds( pnt_num ) );
  }
  glEnd();

  // Draw the second half of the circle
  glColor3d( 0.0, 0.0, 0.0 );
  glPushMatrix();
  glRotated( 180.0, 0.0, 0.0, 1.0 );
  glBegin( GL_POLYGON );
  for( int pnt_num = 0; pnt_num < m_x_crds.size(); ++pnt_num )
  {
    glVertex2d( m_x_crds( pnt_num ), m_y_crds( pnt_num ) );
  }
  glEnd();
  glPopMatrix();

  glPopAttrib();
}