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
#include "../gmlib/modules/parametrics/src/curves/gmpsubcurve.h"


//namespace GMlib {


//*****************************************
// Constructors and destructor           **
//*****************************************

//template <typename T>
//inline
//CurveBlend2<T>::CurveBlend2( GMlib::PCurve<T, 3>* c, int n )  {
//    _d = 1;
//    _n=n;
//    _lc.setDim(n);
//    generateKnotVector(n);
//    for (int i=0;i<n;i++){
//        GMlib::PCurve<T,3>* cu = new GMlib::PSubCurve<T>(c, _t[i],_t[i+2],_t[i+1]);
//        _lc[i]=cu;
//        cu->toggleDefaultVisualizer();
//        cu->replot(20,1);
//        this->insert(cu);

//        //GMlib::Selector<T,3>* s = new GMlib::Selector<T,3>(_c[i],i,this);
//        //this->insert(s);
//    }
//    //auto sk = new GMlib::SelectorGridVisualizer<T>;
//    //sk->setSelectors(_c,0,isClosed());
//    //this->insertVisualizer(sk);


//    //this->_type_id = GM_SO_TYPE_CURVE_BSPLN;
//}

template <typename T>
inline
CurveBlend2<T>::CurveBlend2( GMlib::PCurve<T,3 >* c1, GMlib::PCurve<T,3>* c2, T x) {
       _x = x;
       _c1 = c1;
       _c2 = c2;
}

template <typename T>
inline
CurveBlend2<T>::CurveBlend2( const CurveBlend2<T>& copy ) : GMlib::PCurve<T,3>(copy) {}


template <typename T>
CurveBlend2<T>::~CurveBlend2() {}


//**************************************
//        Public local functons       **
//**************************************

template <typename T>
inline
T CurveBlend2<T>::getDegree() const {
    return _d;
}


template <typename T>
inline
void CurveBlend2<T>::setDegree( int d ) {
    _d = d;
}


//***************************************************
// Overrided (public) virtual functons from PCurve **
//***************************************************

template <typename T>
bool CurveBlend2<T>::isClosed() const {
    return true;
}


//******************************************************
// Overrided (protected) virtual functons from PCurve **
//******************************************************

template <typename T>
void CurveBlend2<T>::eval( T t, int d, bool /*l*/ ) const {
    this->_p.setDim( d + 1 );
        if (t < _c1->getParEnd() - _x*_c1->getParDelta()){
            this->_p = _c1->evaluateParent(t,0);
        }
        else if (t < _c1->getParEnd()){
            T _t1 = (t-_c1->getParEnd()+_x*_c1->getParDelta())/(_x*_c1->getParDelta());

            const T b1 = 1-Bfunc(_t1);
            const T b2 = Bfunc(_t1);

            this->_p = b1*_c1->evaluateParent(t,0) + b2*_c2->evaluateParent(_c2->getParStart()+_t1*_x*_c2->getParDelta(),0);
            //_C[i-2]*b1 + _C[i-1]*b2 + _C[i]*b3;
        }
        else

          this->_p = _c2->evaluateParent(_c2->getParStart()+t-_c1->getParEnd()+_x*_c2->getParDelta(),0);

}

template <typename T>
inline
void CurveBlend2<T>::generateKnotVector(int n) {

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
    qDebug()<<" "<<_t<<" ";
}

template <typename T>
T CurveBlend2<T>::getStartP() const {
    //return T(tmin);
    return _c1->getParStart();
}


template <typename T>
T CurveBlend2<T>::getEndP()const {
    return _c1->getParEnd()+(1-_x)*_c2->getParDelta();
}



template <typename T>
inline
int CurveBlend2<T>::findIndex(T t) const {
    int i=_d;

    for (;i<_n; i++){
        //if (t>=_t[i]&&t<t[i+1]) because in cost function _t[i]=_t(i) for vectors
        if (t>=_t(i) && t<_t(i+1)) break;
    }
    if (i>=_n)
        i=_n-1;
    return i;
}

//template <typename T>
//inline
//T CurveBlend2<T>::_W(int i, int d, T t)const {

//    return (t-_t(i))/(_t(i+d)-_t(i));
//}


//template <typename T>
//void CurveBlend2<T>::createMatrix( GMlib::DMatrix<T>& mat, int n, int m, int d) const {
//    mat.setDim( m, n );
//    for (int j=0;j<m;j++){
//        for(int i=0;i<n;i++)
//            mat[j][i]=T(0);
//        T s=_t(_d);
//        T td= _t(n);
//        T t=s+j*td/(m-1);
//        int i = findIndex(t);
//        T b1=(1-_W(i,1,t))*(1-_W(i-1,2,t));
//        T b2=(1-_W(i,1,t))*_W(i-1,2,t) + (_W(i,1,t))*(1-_W(i,2,t));
//        T b3=_W(i,1,t)*_W(i,2,t);
//        mat[j][i-2]=b1;
//        mat[j][i-1]=b2;
//        mat[j][i]=b3;
//        std::cout<<"t "<<t<<" i"<<i<<std::endl;
//    }

//    //qDebug()<<mat;
//}


//template <typename T>
//void CurveBlend2<T>::lSq( const GMlib::DMatrix<T>& mat, const GMlib::DVector<GMlib::Vector<T,3>>& P){
//    GMlib::DMatrix<T>  matA = mat;
//    matA.transpose();
//    GMlib::DMatrix<T> B=matA*mat;
//    B.invert();
//    GMlib::DVector<GMlib::Vector<T,3>> vec=matA*P;
//    _c=B*vec;

//}

template <typename T>
inline
T CurveBlend2<T>::Bfunc(T t) const{
    return (3*t*t-2*t*t*t);
}
template <typename T>
void CurveBlend2<T>::localSimulate(double dt)
{
    for (int i=0;i<_n;i++){
    //_lc[i]->rotate(1, GMlib::Vector<float, 3> (1,0,0));
    }
}

//} // END namespace GMlib
