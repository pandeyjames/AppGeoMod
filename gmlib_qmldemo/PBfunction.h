
#ifndef GM_PARAMETRICS_CURVES_PBFUNCTION
#define GM_PARAMETRICS_CURVES_PBFUNCTION


#include "../gmlib/modules/parametrics/src/gmpcurve.h"


template <typename T>
class PBfunction : public GMlib::PCurve<T,3> {
    GM_SCENEOBJECT(PBfunction)
public:
    PBfunction( GMlib::PCurve<T, 3>* c1, GMlib::PCurve<T, 3>* c2, T n );
    PBfunction( GMlib::PCurve<T, 3>* c, int n );
    PBfunction( const PBfunction<T>& copy );
    virtual ~PBfunction();

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
    GMlib::DVector<GMlib::PCurve<T, 3>* >   _lc;
    GMlib::DVector< GMlib::Vector<T,3> >    _c1,_c2; // control points (controlpolygon)
    int                                     _d; // polynomial degree
    int                                     _n,n1,n2;
    GMlib::DVector<T>                       _t; // knot vector
    //T              _W(int i, int d, T t) const;
    //void           createMatrix( GMlib::DMatrix<T>& mat, int n, int m, int d) const;
    //void           lSq( const GMlib::DMatrix<T>& mat, const GMlib::DVector<GMlib::Vector<T,3>>& P);
    T              Bfunc(T t) const;
    int            findIndex( T t) const;
    void           generateKnotVector(int n);
    void           localSimulate(double dt) override;

}; // END class PBfunction

//} // END namepace GMlib

// Include PCircle class function implementations
#include "PBfunction.c"


#endif// GM_PARAMETRICS_CURVES_PBFUNCTION
