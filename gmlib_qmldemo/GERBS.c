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

//template <typename T>
//inline
//GERBS<T>::GERBS( const GMlib::DVector< GMlib::Vector<T, 3> >& c,  int d  ) {

//    _c = c;
//    _d = d;
//    _n=_c.getDim();
//    for (int i=0;i<_c.getDim();i++){
//        GMlib::Selector<T,3>* s = new GMlib::Selector<T,3>(_c[i],i,this);
//        this->insert(s);
//    }
//    auto sk = new GMlib::SelectorGridVisualizer<T>;
//    sk->setSelectors(_c,0,isClosed());
//    this->insertVisualizer(sk);
//    generateKnotVector(_c.getDim());

//    //this->_type_id = GM_SO_TYPE_CURVE_BSPLN;
//}

template <typename T>
inline
GERBS<T>::GERBS( GMlib::PCurve<T, 3>*  c, int n) {
    _closed=c->isClosed();
    int n1=_closed? n+1 : n;
    generateKnotVector(n1,c->getParStart(),c->getParEnd());
    _n = n1;
    _lc.setDim(n1);
    for (int i=0;i<n;i++){
        auto s = new GMlib::PSubCurve<T>(c, _t[i],_t[i+2],_t[i+1]);
        s->toggleDefaultVisualizer();
        s->replot(50,0);
        s->setCollapsed(true);

        _lc[i]=s;
        this->insert(s);
    }
//from Igor
//    for(int i=0;i<n;i++){
//            auto cu = new PSubCurve<T>(c,_t[i],_t[i+2],_t[i+1]);
//            cu->toggleDefaultVisualizer();
//            cu->replot(21,0);
//            cu->setCollapsed(true);
//            _C[i] = cu;
//            this->insert(cu);
//        }
//    }
    if(_closed){
        _lc[n]=_lc[0];
    }
}

template <typename T>
inline
GERBS<T>::GERBS( const GERBS<T>& copy ) : GMlib::PCurve<T,3>(copy) {}


template <typename T>
GERBS<T>::~GERBS() {}


//**************************************
//        Public local functons       **
//**************************************




//***************************************************
// Overrided (public) virtual functons from PCurve **
//***************************************************

template <typename T>
bool GERBS<T>::isClosed() const {
    return true;
}


//******************************************************
// Overrided (protected) virtual functons from PCurve **
//******************************************************

template <typename T>
void GERBS<T>::eval( T t, int d, bool /*l*/ ) const {
    this->_p.setDim( d + 1 );
    //int k = (_t.getDim()+1)/3;
    int i = findIndex(t);
    //std::cout<<"i="<<i<<" t="<<t<<std::endl;
    T B = Bfunc((t-_t(i))/(_t(i+1)-_t(i)));
    this->_p=(1-B)*(_lc(i-1)->evaluateParent(t,d))+B*(_lc(i)->evaluateParent(t,d));

}

template <typename T>
inline
void GERBS<T>::generateKnotVector(int n, T s, T e) {

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

    if (_closed){
        _t[0]=_t[1]-(_t[n]-_t[n-1]);
        _t[n+1]=_t[n]+(_t[2]-_t[1]);
    }
    qDebug()<<" _t "<<_t<<" ";
}

template <typename T>
T GERBS<T>::getStartP() const {
    //return T(tmin);
    return _t(1);
}




template <typename T>
T GERBS<T>::getEndP()const {
    //return T(tmax);
    return _t( _t.getDim()-2 );
}



template <typename T>
inline
int GERBS<T>::findIndex(T t) const {
    int i=1;

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
T GERBS<T>::Bfunc(T t) const{
    return (3*t*t-2*t*t*t);
}

template <typename T>
void GERBS<T>::localSimulate(double dt)
{
//    for (int i=0;i<_n;i++){
//    _lc[i]->rotate(dt, GMlib::Vector<float, 3> (1,1,0));
//    }


       for(int i=0;i<_lc.getDim();i++){
           _lc[i]->rotate(1 , GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f*dt) );
           _lc[i]->rotate(dt , GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f) );
           _lc[i]->rotate(dt , GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f) );
           _lc[i]->rotate(dt , GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f) );

    }
    }
    //std::cout<<dt;
//} // END namespace GMlib
