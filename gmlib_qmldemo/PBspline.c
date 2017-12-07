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

#include <QDebug>
#include "../gmlib/modules/scene/src/visualizers/gmselectorgridvisualizer.h"



//namespace GMlib {


//*****************************************
// Constructors and destructor           **
//*****************************************

template <typename T>
inline
PBspline<T>::PBspline( const GMlib::DVector< GMlib::Vector<T, 3> >& c,  int d  ) {

    _c = c;
    _d = d;
    _n=_c.getDim();
    for (int i=0;i<_c.getDim();i++){
        GMlib::Selector<T,3>* s = new GMlib::Selector<T,3>(_c[i],i,this);
        this->insert(s);
//        s->toggleDefaultVisualizer();
//        s->replot(50,0);
//        s->setCollapsed(true);
    }
    auto sk = new GMlib::SelectorGridVisualizer<T>;
    sk->setSelectors(_c,0,isClosed());
    this->insertVisualizer(sk);

    generateKnotVector(_c.getDim());

    //this->_type_id = GM_SO_TYPE_CURVE_BSPLN;
}

template <typename T>
inline
PBspline<T>::PBspline( const GMlib::DVector< GMlib::Vector<T, 3> >& p,  int d, int n) {

    _d = d;
    _n = n;
    int m = p.getDim();

    generateKnotVector(n);
    GMlib::DMatrix<T>  mat;
    createMatrix(mat,n,m,d);
    lSq(mat,p);
    //this->_type_id = GM_SO_TYPE_CURVE_BSPLN;
}

template <typename T>
inline
PBspline<T>::PBspline( const PBspline<T>& copy ) : GMlib::PCurve<T,3>(copy) {}


template <typename T>
PBspline<T>::~PBspline() {}


//**************************************
//        Public local functons       **
//**************************************

template <typename T>
inline
T PBspline<T>::getDegree() const {
    return _d;
}


template <typename T>
inline
void PBspline<T>::setDegree( int d ) {
    _d = d;
}


//***************************************************
// Overrided (public) virtual functons from PCurve **
//***************************************************

template <typename T>
bool PBspline<T>::isClosed() const {
    return true;
}


//******************************************************
// Overrided (protected) virtual functons from PCurve **
//******************************************************

template <typename T>
void PBspline<T>::eval( T t, int d, bool /*l*/ ) const {
    this->_p.setDim( d + 1 );
    //int k = (_t.getDim()+1)/3;
    int i = findIndex(t);
    T b1=(1-_W(i,1,t))*(1-_W(i-1,2,t));
    T b2=(1-_W(i,1,t))*_W(i-1,2,t) + (_W(i,1,t))*(1-_W(i,2,t));
    T b3=_W(i,1,t)*_W(i,2,t);

    //qDebug()<<"t="<<t<<" i="<<i;

    this->_p[0] = _c[i-2]*b1+_c[i-1]*b2+_c[i]*b3;

}

template <typename T>
inline
void PBspline<T>::generateKnotVector(int n) {

    int order = getDegree() + 1;

    _t.setDim( n + order );
    int step_knots = _t.getDim() - ( order * 2 );

    T knot_value = T(0);
    int i = 0;

    // Set the start knots
    for( ; i < order; i++ )
        _t[i] = knot_value;

    // Set the "step"-knots
    for( int j = 0; j < step_knots; j++ )
        _t[i++] = ++knot_value;

    // Set the end knots
    knot_value++;
    for( ; i < _t.getDim(); i++ ){
        _t[i] = knot_value;

    }
    //qDebug()<<" "<<_t<<" ";
}

template <typename T>
T PBspline<T>::getStartP() const {
    //return T(tmin);
    return _t(_d);
}




template <typename T>
T PBspline<T>::getEndP()const {
    //return T(tmax);
    return _t( _c.getDim() );
}



template <typename T>
inline
int PBspline<T>::findIndex(T t) const {
    int i=_d;

    for (;i<_n; i++){
        //if (t>=_t[i]&&t<t[i+1]) because in cost function _t[i]=_t(i) for vectors
        if (t>=_t(i) && t<_t(i+1)) break;
    }
    if (i>=_n)
        i=_n-1;
    return i;
}

template <typename T>
inline
T PBspline<T>::_W(int i, int d, T t)const {

    return (t-_t(i))/(_t(i+d)-_t(i));
}


template <typename T>
void PBspline<T>::createMatrix( GMlib::DMatrix<T>& mat, int n, int m, int d) const {
    mat.setDim( m, n );
    for (int j=0;j<m;j++){
        for(int i=0;i<n;i++)
            mat[j][i]=T(0);
        T s=_t(_d);
        T td= _t(n);
        T t=s+j*td/(m-1);
        int i = findIndex(t);
        T b1=(1-_W(i,1,t))*(1-_W(i-1,2,t));
        T b2=(1-_W(i,1,t))*_W(i-1,2,t) + (_W(i,1,t))*(1-_W(i,2,t));
        T b3=_W(i,1,t)*_W(i,2,t);
        mat[j][i-2]=b1;
        mat[j][i-1]=b2;
        mat[j][i]=b3;
//std::cout<<"t "<<t<<" i"<<i<<std::endl;
    }

        //qDebug()<<mat;
}


template <typename T>
void PBspline<T>::lSq( const GMlib::DMatrix<T>& mat, const GMlib::DVector<GMlib::Vector<T,3>>& P){
    GMlib::DMatrix<T>  matA = mat;
    matA.transpose();
    GMlib::DMatrix<T> B=matA*mat;
    B.invert();
    GMlib::DVector<GMlib::Vector<T,3>> vec=matA*P;
    _c=B*vec;

    }
//} // END namespace GMlib
