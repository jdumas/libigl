// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2019 Jérémie Dumas <jeremie.dumas@ens-lyon.org>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "texture_from_colormap.h"

template <typename Derived>
IGL_INLINE void igl::opengl::texture_from_colormap(
  const Eigen::MatrixBase<Derived> & r,
  const Eigen::MatrixBase<Derived> & g,
  const Eigen::MatrixBase<Derived> & b,
  const Eigen::MatrixBase<Derived> & a,
  GLuint & id)
{
  assert(r.size() == g.size() && g.size() == b.size());
  int width = 1;
  int height = (int) r.rows();

  Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> cmap(height, 4);
  cmap.col(0) = r.template cast<unsigned char>();
  cmap.col(1) = g.template cast<unsigned char>();
  cmap.col(2) = b.template cast<unsigned char>();
  if (a.size() == 0) {
    cmap.col(3).setConstant(255);
  } else {
    assert(a.size() == r.size());
    cmap.col(3) = a;
  }

  if (id == 0) {
    glGenTextures(1, &id);
  }
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGBA,
    width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cmap.data());
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

template <typename Derived>
IGL_INLINE void igl::opengl::texture_from_colormap(
  const Eigen::MatrixBase<Derived> & rgba,
  GLuint & id)
{
  texture_from_colormap(rgba.col(0), rgba.col(1), rgba.col(2), rgba.col(3), id);
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
#endif

