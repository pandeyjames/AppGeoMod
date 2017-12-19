
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
    GERBSURFACE( GMlib::PSurf<T, 3>*  s, int n1, int n2 );

    GERBSURFACE( const GERBSURFACE<T>& copy );
    virtual ~GERBSURFACE();

    // Public local functions



    //****************************************
    //****** Virtual public functions   ******
    //****************************************

    // from PCurve
    bool                isClosedU() const override;
    bool                isClosedV() const override;

protected:
    // Virtual function from PCurve that has to be implemented locally
    void                eval(T tu, T tv, int d1, int d2, bool l = true, bool k = true ) const override;
    T                   getStartPU() const override;
    T                   getEndPU()   const override;
    T                   getStartPV() const override;
    T                   getEndPV()   const override;


    // Protected data for the curve
    // Protected data for the curve
    GMlib::DMatrix< GMlib::PSurf<T,3>* >   _ls; // local surfaces

    int                                     _n1,_n2;
    GMlib::DVector<T>                       _u; // knot vector
    GMlib::DVector<T>                       _v; // knot vector
    T               Bfunc(T t) const;
    T               BfuncD(T t) const;
    T              _W(int i, int d, T t,const GMlib::DVector<T>& k) const;
    void lSq( const GMlib::DMatrix<T>& mat, const GMlib::DVector<GMlib::Vector<T,3>>& P);
    int            findIndex( T t,const GMlib::DVector<T>& k) const;
    void           generateKnotVector(GMlib::DVector<T> &_t,int n, T s, T e, bool closed);
    bool           _closed_u;
    bool           _closed_v;
    void           localSimulate(double dt) override;

}; // END class GERBSURFACE

//} // END namepace GMlib

// Include PCircle class function implementations
#include "GERBSURFACE.c"


#endif// GM_PARAMETRICS_CURVES_GERBSURFACE
