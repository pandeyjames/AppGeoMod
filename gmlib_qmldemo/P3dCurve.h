
#ifndef GM_PARAMETRICS_CURVES_P3DCurve
#define GM_PARAMETRICS_CURVES_P3DCurve


#include "../gmlib/modules/parametrics/src/gmpcurve.h"
#include "strings.h"


//namespace GMlib {


  template <typename T>
  class P3DCurve : public GMlib::PCurve<T,3> {
    GM_SCENEOBJECT(P3DCurve)
public:
    P3DCurve( T radius = T(5));
    P3DCurve( T x, T y, T z, T min, T max );
    P3DCurve( const P3DCurve<T>& copy );
    virtual ~P3DCurve();

    // Public local functions
    T               getRadius() const;
    void            setRadius( T radius = T(5) );

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
    T                         _r,_t;
    //std::string               _x, _y, _z, tmin,tmax;
    T parseFunc(T x);

  }; // END class P3DCurve

//} // END namepace GMlib

// Include PCircle class function implementations
#include "P3DCurve.c"


#endif// GM_PARAMETRICS_CURVES_P3DCurve
