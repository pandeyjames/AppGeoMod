/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/





#ifndef MYGERBSSURFACE_H
#define MYGERBSSURFACE_H

#include "parametrics/gmpsurf.h"
#include "parametrics/gmpsubsurf"

namespace GMlib {

  template <typename T>
  class MyGERBSSurface : public PSurf<T,3> {
    GM_SCENEOBJECT(MyGERBSSurface)
  public:
        MyGERBSSurface( PSurf<T,3>* s, int nu,  int nv, int du = 0, int dv = 0);
        MyGERBSSurface( const MyGERBSSurface<T>& copy );
    virtual ~MyGERBSSurface();

    //***************************************
    //****** Virtual public functions  ******
    //***************************************

    // from PSurf
    bool          isClosedU()  const override;
    bool          isClosedV()  const override;
    DMatrix< PSubSurf<T>* >      getSubSurfaces();
  protected:
    // Virtual function from PSurf that has to be implemented locally
    void          eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true ) const override;
    T             getStartPU() const override;
    T             getEndPU()   const override;
    T             getStartPV() const override;
    T             getEndPV()   const override;

    int                       getIndexU(T t) const;
    int                       getIndexV(T t) const;
    T                         getWu( T t, int idx, int d ) const;
    T                         getWv( T t, int idx, int d ) const;
    T                         getWuDer( T t, int idx, int d ) const;
    T                         getWvDer( T t, int idx, int d ) const;

    T                         bFunction(T t) const;
    T                         bFunctionDer(T t) const;

    // Protected data for the surface
    PSurf<T,3>* plane;
    mutable
    DMatrix< PSubSurf<T>* >     _s;       // control polygon

    DVector<T>                 _u;       // knot vector in u-direction
    int                        _du;      // degree in u-direction
//      int                        _ku;      // order in u-direction, _ku = _du+1
    bool                       _cu;      // closed in u-direction

    DVector<T>                 _v;       // knot vector in v-direction
    int                        _dv;      // degree in v-direction
//      int                        _kv;      // order in v-direction, _kv = _dv+1
    bool                       _cv;

  }; // END class

} // END namespace GMlib

// Include PPlane class function implementations
#include "mygerbssurface.c"



#endif
