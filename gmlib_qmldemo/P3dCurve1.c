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



#include "exprtk.h"

//namespace GMlib {


//*****************************************
// Constructors and destructor           **
//*****************************************

  template <typename T>
  inline
  P3DCurve1<T>::P3DCurve1( T radius ) {
    _r = radius;
  }

  template <typename T>
  inline
  P3DCurve1<T>::P3DCurve1( T x, T y, T z, T min, T max ) {
//    _x = x;
//    _y = y;
//    _z = z;
//    tmin = min;
//    tmax = max;
  }

  template <typename T>
  inline
  P3DCurve1<T>::P3DCurve1( const P3DCurve1<T>& copy ) : GMlib::PCurve<T,3>(copy) {}


  template <typename T>
  P3DCurve1<T>::~P3DCurve1() {}


  //**************************************
  //        Public local functons       **
  //**************************************

  template <typename T>
  inline
  T P3DCurve1<T>::getRadius() const {
    return _r;
  }


  template <typename T>
  inline
  void P3DCurve1<T>::setRadius( T radius ) {
      _r = radius;
  }


  //***************************************************
  // Overrided (public) virtual functons from PCurve **
  //***************************************************

  template <typename T>
  bool P3DCurve1<T>::isClosed() const {
    return true;
  }


  //******************************************************
  // Overrided (protected) virtual functons from PCurve **
  //******************************************************

  template <typename T>
  void P3DCurve1<T>::eval( T t, int d, bool /*l*/ ) const {

    this->_p.setDim( d + 1 );
      //_t=t;

      const T ct = sin(t)+sin(t)*sin(6*t);//t * cos(t);
      const T st = cos(t)+cos(t)*sin(6*t);//t * sin(t);

      this->_p[0][0] = ct;
      this->_p[0][1] = st;
      this->_p[0][2] = 0;//t;


//      const T ct = parseFunc(_x);//t * cos(t);
//      const T st = parseFunc(_y);//t * sin(t);
//      const T bt = parseFunc(_z);//sin(6*t);

//      this->_p[0][0] = ct;
//      this->_p[0][1] = st;
//      this->_p[0][2] = bt;

//    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

//      if( d > 0 ) {
//        this->_p[1][0] = -st;
//        this->_p[1][1] =  ct;
//        this->_p[1][2] =  T(0);
//      }
//      if( d > 1 ) this->_p[2] = -this->_p[0];
//      if( d > 2 ) this->_p[3] = -this->_p[1];
//      if( d > 3 ) this->_p[4] = this->_p[0];
//      if( d > 4 ) this->_p[5] = this->_p[1];
//      if( d > 5 ) this->_p[6] = this->_p[2];
//      if( d > 6 ) this->_p[7] = this->_p[3];
//    }
  }


  template <typename T>
  T P3DCurve1<T>::getStartP() const {
    //return T(tmin);
      return T(0);
  }

  template <typename T>
  T P3DCurve1<T>::getEndP()const {
    //return T(tmax);
      return T( M_2PI);
  }

//} // END namespace GMlib
