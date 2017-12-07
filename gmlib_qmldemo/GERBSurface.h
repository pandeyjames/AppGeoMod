
#ifndef GM_PARAMETRICS_CURVES_GERBSURFACE
#define GM_PARAMETRICS_CURVES_GERBSURFACE

/*
Implement your own version of a GERBS surface of blending spline type.
Use PSimpleSubSurf as local surface
Do static transformation to create a new shape.
*/
#include "simplesubsurf.h"


template <typename T>
class GERBSURFACE : public GMlib::PSurf<T,3> {
    GM_SCENEOBJECT(GERBSURFACE)
public:
    GERBSURFACE( GMlib::PSurf<T, 3>*  c, int n1, int n2 );

    GERBSURFACE( const GERBSURFACE<T>& copy );
    virtual ~GERBSURFACE();

    // Public local functions



    //****************************************
    //****** Virtual public functions   ******
    //****************************************

    // from PCurve
    bool                isClosed() const override;

protected:
    // Virtual function from PCurve that has to be implemented locally
    void                eval(T t, int d, bool l = true ) const override;
    T                   getStartPu() const override;
    T                   getEndPu()   const override;
    T                   getStartPv() const override;
    T                   getEndPv()   const override;


    // Protected data for the curve
    // Protected data for the curve
    GMlib::DVector< GMlib::PSurf<T,3>* >   _ls; // local surfaces

    int                                     _n;
    GMlib::DVector<T>                       _t; // knot vector
    T               Bfunc(T t) const;
    T              _W(int i, int d, T t) const;
    void lSq( const GMlib::DMatrix<T>& mat, const GMlib::DVector<GMlib::Vector<T,3>>& P);
    int            findIndex( T t) const;
    void           generateKnotVector(int n, T s, T e);
    bool           _closed;

}; // END class GERBSURFACE

//} // END namepace GMlib

// Include PCircle class function implementations
#include "GERBSURFACE.c"


#endif// GM_PARAMETRICS_CURVES_GERBSURFACE
