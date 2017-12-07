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
GERBSURFACE<T>::GERBSURFACE( GMlib::PSurf<T, 3>*  s, int n1, int n2) {
    _closed=s->isClosed();
    int n1=_closed? n+1 : n;
    generateKnotVector(n1,s->getParStart(),s->getParEnd());
    _n = n1;
    _ls.setDim(n1);
    for (int i=0;i<n;i++){
        auto s = new PSubSurf<T>(s, _t[i],_t[i+2],_t[i+1]);

        s->toggleDefaultVisualizer();
        s->replot(50,0);
        s->setCollapsed(true);
        _ls[i]=s;
        this->insert(s);

    }

    if(_closed){
        _ls[n]=_ls[0];
    }

}

template <typename T>
inline
GERBSURFACE<T>::GERBSURFACE( const GERBSURFACE<T>& copy ) : GMlib::PCurve<T,3>(copy) {}


template <typename T>
GERBSURFACE<T>::~GERBSURFACE() {}


//**************************************
//        Public local functons       **
//**************************************




//***************************************************
// Overrided (public) virtual functons from PCurve **
//***************************************************

template <typename T>
bool GERBSURFACE<T>::isClosed() const {
    return true;
}


//******************************************************
// Overrided (protected) virtual functons from PCurve **
//******************************************************

template <typename T>
void GERBSURFACE<T>::eval( T t, int d, bool /*l*/ ) const {
    this->_p.setDim( d + 1 );
    //int k = (_t.getDim()+1)/3;
    int i = findIndex(t);
    T B = Bfunc((t-_t(i))/(_t(i+1)-_t(i)));
    this->_p=(1-B)*(_lc(i-1)->evaluateParent(t,d))+B*(_lc(i)->evaluateParent(t,d));

}

template <typename T>
inline
void GERBSURFACE<T>::generateKnotVector(int n, T s, T e) {

    int order = 2;

    _t.setDim( n + order );
    int step_knots = _t.getDim() - ( order * 2 );

    T knot_value = (e-s)/(n-1);
    int i = 0;

    // Set the start knots
    for( ; i < order; i++ )
        _t[i] = s;

    // Set the "step"-knots
    for( int j = 1; j <= step_knots; j++ )
        _t[i++] = s+j*knot_value;

    for( ; i < _t.getDim(); i++ ){
        _t[i] = e;

    }
    qDebug()<<" "<<_t<<" ";
}

template <typename T>
T GERBSURFACE<T>::getStartPu() const {
    //return T(tmin);
    return _t(1);
}




template <typename T>
T GERBSURFACE<T>::getEndPu()const {
    //return T(tmax);
    return _t( _t.getDim()-2 );
}

template <typename T>
T GERBSURFACE<T>::getStartPv() const {
    //return T(tmin);
    return _t(1);
}




template <typename T>
T GERBSURFACE<T>::getEndPv()const {
    //return T(tmax);
    return _t( _t.getDim()-2 );
}




template <typename T>
inline
int GERBSURFACE<T>::findIndex(T t) const {
    int i=2;

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
T GERBSURFACE<T>::_W(int i, int d, T t)const {

    return (t-_t(i))/(_t(i+d)-_t(i));
}
template <typename T>
inline
T GERBSURFACE<T>::Bfunc(T t) const{
    return (3*t*t-2*t*t*t);
}

//template <typename T>
//void GERBSURFACE<T>::localSimulate(double dt)
//{
//    for (int i=0;i<_n;i++){
//    _lc[i]->rotate(1, GMlib::Vector<float, 3> (1,0,0));
//    }
//}
//} // END namespace GMlib
