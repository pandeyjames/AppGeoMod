
#ifndef GM_PARAMETRICS_CURVES_GERBS
#define GM_PARAMETRICS_CURVES_GERBS

/*
Implement your own version of a GERBS curve of blending spline type.
Implement your own B-function.
Use GMlib::PSubCurve as local curves.
make an GERBS copy of your model curve.

*/
#include "../gmlib/modules/parametrics/src/gmpcurve.h"


template <typename T>
class GERBS : public GMlib::PCurve<T,3> {
    GM_SCENEOBJECT(GERBS)
public:
    GERBS( GMlib::PCurve<T, 3>*  c, int n );

    GERBS( const GERBS<T>& copy );
    virtual ~GERBS();

    // Public local functions



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
    // Protected data for the curve
    GMlib::DVector< GMlib::PCurve<T,3>* >   _lc; // local curves

    int                                     _n;
    GMlib::DVector<T>                       _t; // knot vector
    T              Bfunc(T t) const;
    void lSq( const GMlib::DMatrix<T>& mat, const GMlib::DVector<GMlib::Vector<T,3>>& P);
    int            findIndex( T t) const;
    void           generateKnotVector(int n, T s, T e);
    void           localSimulate(double dt) override;
    bool           _closed;

}; // END class GERBS

//} // END namepace GMlib

// Include PCircle class function implementations
#include "GERBS.c"


#endif// GM_PARAMETRICS_CURVES_GERBS
