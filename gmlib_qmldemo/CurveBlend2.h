
#ifndef GM_PARAMETRICS_CURVES_CURVEBLEND2
#define GM_PARAMETRICS_CURVES_CURVEBLEND2


#include "../gmlib/modules/parametrics/src/gmpcurve.h"

//You shall implement a curve resulting from blending two curves with a B function over a given part of the two curves.
template <typename T>
class CurveBlend2 : public GMlib::PCurve<T,3> {
    GM_SCENEOBJECT(CurveBlend2)
public:
    CurveBlend2( GMlib::PCurve<T, 3>* c1, GMlib::PCurve<T, 3>* c2, T x );
    CurveBlend2( const CurveBlend2<T>& copy );
    virtual ~CurveBlend2();

    // Public local functions
    T               getDegree() const;
    void            setDegree( int d);



    //****************************************
    //****** Virtual public functions   ******
    //****************************************

    // from PCurve
    bool                isClosed() const override;

protected:
    // Virtual function from PCurve that has to be implemented locally
    void                eval(T t, int d, bool l = true ) const override;
    T                   getStartP() const override;
    T                   getEndP()   const override;

    // Protected data for the curve
    GMlib::PCurve<T, 3>*                      _c1;
    GMlib::PCurve<T, 3>*                      _c2;
    //GMlib::DVector< GMlib::Vector<T,3> >    _c1,_c2; // control points (controlpolygon)
    int                                     _d; // polynomial degree
    int                                     _n,n1,n2;
    T                                         _x;
    GMlib::DVector<T>                       _t; // knot vector
    //T              _W(int i, int d, T t) const;
    //void           createMatrix( GMlib::DMatrix<T>& mat, int n, int m, int d) const;
    //void           lSq( const GMlib::DMatrix<T>& mat, const GMlib::DVector<GMlib::Vector<T,3>>& P);
    T              Bfunc(T t) const;
    int            findIndex( T t) const;
    void           generateKnotVector(int n);
    void           localSimulate(double dt) override;

}; // END class CurveBlend2

//} // END namepace GMlib

// Include PCircle class function implementations
#include "CurveBlend2.c"


#endif// GM_PARAMETRICS_CURVES_CURVEBLEND2
