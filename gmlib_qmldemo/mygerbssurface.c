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


// gmlib
//#include <core/containers/gmdmatrix.h>
//#include <scene/selector/gmselector.h>


namespace GMlib {


//*****************************************
// Constructors and destructor           **
//*****************************************

template <typename T>
inline
MyGERBSSurface<T>::MyGERBSSurface(PSurf<T,3>* s, int nu,  int nv, int /*du*/, int /*dv*/) {

    //      init();
    // set knot vector in u direction
    _u.setDim(nu+3);
    _u[0]=s->getParStartU();
    _u[1]=_u[0];
    _u[nu+1]=s->getParEndU();
    _u[nu+2]=_u[nu+1];
    for (int i = 2; i < nu+1; i++){
        _u[i] = _u[0]+T((i-1)*(_u[nu+1]-_u[0])/nu);
    }
    // set knot vector in v direction
    _v.setDim(nv+3);
    _v[0]=s->getParStartV();
    _v[1]=_v[0];
    _v[nv+1]=s->getParEndV();
    _v[nv+2]=_v[nv+1];
    for (int i = 2; i < nv+1; i++){
        _v[i] = _v[0]+T((i-1)*(_v[nv+1]-_v[0])/nv);
    }
    // create sub surfaces
    _s.setDim(nu+1,nv+1);
    for (int i=0;i<nu+1;i++){
        for (int j=0;j<nv+1;j++){
            _s[i][j]= new PSubSurf<T>(s, _u[i], _u[i+2], _v[j], _v[j+2]);
        }
    }

    std::cout<<_u<<std::endl;
    std::cout<<_v<<std::endl;
    _cu=false;
    _cv=false;
    _du=1;
    _dv=1;
    plane=s;
}


template <typename T>
inline
MyGERBSSurface<T>::MyGERBSSurface( const MyGERBSSurface<T>& copy ) : PSurf<T,3>( copy ) {

//    init();

    _s = copy._s;
    _u = copy._u;
    _v = copy._v;
    //      _ku = copy._ku;
    //      _kv = copy._kv;
    //      _du = copy._du;
    //      _dv = copy._dv;
    //      _cu = copy._cu;
    //      _cv = copy._cv;
}



template <typename T>
MyGERBSSurface<T>::~MyGERBSSurface() {

}

template <typename T>
DMatrix< PSubSurf<T>* > MyGERBSSurface<T>::getSubSurfaces(){
    return _s;
}


  //*****************************************
  //            Local functons             **
  //*****************************************










template <typename T>
int  MyGERBSSurface<T>::getIndexU(T t) const{

    int idx;

    // Calculate index
    idx = 1;
    while( t > _u[idx+1] )
        idx++;
    return idx;
}
template <typename T>
int  MyGERBSSurface<T>::getIndexV(T t) const{

    int idx;

    // Calculate index
    idx = 1;
    while( t > _v[idx+1] )
        idx++;
    return idx;
}
template <typename T>
inline
T MyGERBSSurface<T>::getWu( T t, int idx, int d ) const {

    return ( t - _u(idx) ) / ( _u(idx+d) - _u(idx) );
}

template <typename T>
inline
T MyGERBSSurface<T>::getWv( T t, int idx, int d ) const {

    return ( t - _v(idx) ) / ( _v(idx+d) - _v(idx) );
}
template <typename T>
inline
T MyGERBSSurface<T>::bFunction(T t) const{
//    T s =sin(M_PI/2*t);
//    return s*s;
    return T(t*t/((1-t)*(1-t)+t*t));
}

  template <typename T>
  inline
  T MyGERBSSurface<T>::getWuDer( T t, int idx, int d ) const {

    return T(1) / ( _u(idx+d) - _u(idx) );
  }
  template <typename T>
  inline
  T MyGERBSSurface<T>::getWvDer( T t, int idx, int d ) const {

    return T(1) / ( _v(idx+d) - _v(idx) );
  }

  template <typename T>
  inline
  T MyGERBSSurface<T>::bFunctionDer(T t) const{
//      return M_PI*cos(M_PI/2*t)*sin(M_PI/2*t);
      return T(2*t*(1-t)/(((1-t)*(1-t)+t*t)*((1-t)*(1-t)+t*t)));
  }



  //**************************************************
  // Overrided (public) virtual functons from PSurf **
  //**************************************************


  template <typename T>
  bool MyGERBSSurface<T>::isClosedU() const {
      return _cu;
  }


  template <typename T>
  bool MyGERBSSurface<T>::isClosedV() const {
      return _cv;
  }



  //*****************************************************
  // Overrided (protected) virtual functons from PSurf **
  //*****************************************************
  template <typename T>
  void MyGERBSSurface<T>::eval( T u, T v, int du, int dv, bool lu, bool lv ) const {
  //    int nu=_s.getDim1();
  //    int nv=_s.getDim2();
      int intervalu = getIndexU(u);
      int intervalv = getIndexV(v);
      int uindx1=intervalu-1;
      int uindx2=intervalu;
      int vindx1=intervalv-1;
      int vindx2=intervalv;


      DMatrix<DMatrix<Vector<float,3>>> C(2,2);
      C[0][0]=_s[uindx1][vindx1]->evaluateParent(u,v,du,dv);
      C[1][0]=_s[uindx2][vindx1]->evaluateParent(u,v,du,dv);
      C[0][1]=_s[uindx1][vindx2]->evaluateParent(u,v,du,dv);
      C[1][1]=_s[uindx2][vindx2]->evaluateParent(u,v,du,dv);

      DMatrix<T> Bu(2,2);
      Bu[0][0]=T(1-bFunction(getWu(u,uindx2,1)));
      Bu[0][1]=T(bFunction(getWu(u,uindx2,1)));
      Bu[1][0]=-T(getWuDer(u,uindx2,1)*bFunctionDer(getWu(u,uindx2,1)));
      Bu[1][1]=T(getWuDer(u,uindx2,1)*bFunctionDer(getWu(u,uindx2,1)));

  //    std::cout << Bu<<std::endl;
      DMatrix<T> Bv(2,2);
      Bv[0][0]=T(1-bFunction(getWv(v,vindx2,1)));
      Bv[0][1]=T(bFunction(getWv(v,vindx2,1)));
      Bv[1][0]=-T(getWvDer(v,vindx2,1)*bFunctionDer(getWv(v,vindx2,1)));
      Bv[1][1]=T(getWvDer(v,vindx2,1)*bFunctionDer(getWv(v,vindx2,1)));
  //    Bv.transpose();
  //std::cout << Bv<<std::endl;
  //    std::cout << u << std::endl;
  //    std::cout << intervalu << std::endl;
  //    std::cout << v << std::endl;
  //    std::cout << intervalv << std::endl;
      // blending of 4 patches
      auto original = plane->evaluateParent(u,v,du,dv);
      auto p0=((Bu[0][0]*C[0][0]+Bu[0][1]*C[1][0])*Bv[0][0]+(Bu[0][0]*C[0][1]+Bu[0][1]*C[1][1])*Bv[0][1]);
  //    this->_p[0][0]=p0[0][0];
      this->_p[0][0]=original[0][0];
//      std::cout << "p0" << std::endl;
//      std::cout << p0 << std::endl;
//      std::cout << "position: " << p0[0][0] << std::endl;

      std::cout << "original position: " << original[0][0] << std::endl;
      auto p1=(Bv[1][1]*(Bu[0][0]*(C[0][1]-C[0][0])+Bu[0][1]*(C[1][1]-C[1][0])));
  //    this->_p[0][1]=p1[0][1];
      this->_p[0][1]=original[0][1];
//      std::cout << "p1" << std::endl;
//      std::cout << p1 << std::endl;
//      std::cout << "derivative1:" <<p1[0][1] <<std::endl;
//      std::cout << "original derivative1: " << original[0][1] << std::endl;

      auto p2=(Bu[1][1]*((C[1][0]-C[0][0])*Bv[0][0]+(C[1][1]-C[0][1])*Bv[0][1]));
  //    this->_p[1][0]=p2[1][0];
      this->_p[1][0]=original[1][0];
//      std::cout << "p2" << std::endl;
//      std::cout << p2 << std::endl;
//          std::cout << "derivative2:" <<p2[1][0] <<std::endl;
//          std::cout << "original derivative 2: " << original[1][0] << std::endl;

      auto p3=(Bv[1][1]*Bu[1][1]*(C[1][1]-C[0][1]-C[1][0]+C[0][0]));
  //    this->_p[1][1]=p3[1][1];
      this->_p[1][1]=original[1][1];



  }


  template <typename T>
  T MyGERBSSurface<T>::getEndPU() const {
  //    return _u(_s.getDim1());
      return plane->getParEndU();
  }


  template <typename T>
  T MyGERBSSurface<T>::getEndPV() const {
  //    return _v(_s.getDim2());
      return plane->getParEndV();
  }


  template <typename T>
  T MyGERBSSurface<T>::getStartPU() const {
  //    return _u(1);
      return plane->getParStartU();
  }


  template <typename T>
  inline
  T MyGERBSSurface<T>::getStartPV() const {
  //    return _v(1);
      return plane->getParStartV();
  }




}
