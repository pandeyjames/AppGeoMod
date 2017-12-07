
#ifndef GM_PARAMETRICS_CURVES_PBSPLINE
#define GM_PARAMETRICS_CURVES_PBSPLINE

/*
 * Implement your own version of a 2nd degree B-spline curve
The class must use PCurve as base class
The evaluator only need to compute the value (no derivatives)
Two constructors must be implemented
MyB-spline( const DVector<Vector<float,3>>& c);     // use c as control points - and generate a knotvector
MyB-spline( const DVector<Vector<float,3>>& p, int n);     // use least square to make n control points - and generate a knotvector
*/
#include "../gmlib/modules/parametrics/src/gmpcurve.h"


template <typename T>
class PBspline : public GMlib::PCurve<T,3> {
    GM_SCENEOBJECT(PBspline)
public:
    PBspline( const GMlib::DVector< GMlib::Vector<T, 3> >& c, int d );
    PBspline( const GMlib::DVector< GMlib::Vector<T, 3> >& c, int d, int n );
    PBspline( const PBspline<T>& copy );
    virtual ~PBspline();

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
    // Protected data for the curve
    GMlib::DVector< GMlib::Vector<T,3> >    _c; // control points (controlpolygon)
    int                                     _d; // polynomial degree
    int                                     _n;
    GMlib::DVector<T>                       _t; // knot vector
    T              _W(int i, int d, T t) const;
    void           createMatrix( GMlib::DMatrix<T>& mat, int n, int m, int d) const;
    void lSq( const GMlib::DMatrix<T>& mat, const GMlib::DVector<GMlib::Vector<T,3>>& P);
    int            findIndex( T t) const;
    void           generateKnotVector(int n);

}; // END class PBspline

//} // END namepace GMlib

// Include PCircle class function implementations
#include "PBspline.c"


#endif// GM_PARAMETRICS_CURVES_PBSPLINE
