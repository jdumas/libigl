#ifndef IGL_OPENGL_TEXTURE_FROM_COLORMAP_H
#define IGL_OPENGL_TEXTURE_FROM_COLORMAP_H

#include <igl/opengl/../igl_inline.h>
#include <igl/opengl/gl.h>
#include <Eigen/Core>

namespace igl
{
  namespace opengl
  {
    // Create an OpenGL texture corresponding to the given colormap.
    // The generated texture is a vertical image of 1 x N pixels.
    //
    // Inputs:
    //   R  N x 1 red channel (between 0 and 255)
    //   G  N x 1 green channel (between 0 and 255)
    //   B  N x 1 blue channel (between 0 and 255)
    //   A  (0|N) x 1 alpha channel
    // Outputs:
    //   id  id of generated openGL texture. If != 0 on input, the buffer will be reused.
    //
    template <typename Derived>
    IGL_INLINE void texture_from_colormap(
      const Eigen::MatrixBase<Derived> & r,
      const Eigen::MatrixBase<Derived> & g,
      const Eigen::MatrixBase<Derived> & b,
      const Eigen::MatrixBase<Derived> & a,
      GLuint & id);

    // Same, but takes a N x (3|4) matrix as input
    template <typename Derived>
    IGL_INLINE void texture_from_colormap(
      const Eigen::MatrixBase<Derived> & rgba,
      GLuint & id);

  }
}

#ifndef IGL_STATIC_LIBRARY
#  include "texture_from_colormap.cpp"
#endif

#endif
