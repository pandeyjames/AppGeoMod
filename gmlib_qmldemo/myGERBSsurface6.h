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




#ifndef GM_MyGERBSsurface6_H
#define GM_MyGERBSsurface6_H


//#include "C:\Users\Aleksei\Desktop\applied-geometry-project\gmlib\modules\parametrics\src\gmpcurve.h"
#include "../gmlib/modules/scene/src/selector/gmselector.h"

//namespace GMlib {
#include "simplesubsurf.h"


template <typename T>
class MyGERBSsurface6 : public GMlib::PSurf<T,3> {
    GM_SCENEOBJECT(MyGERBSsurface6)
    public:
        MyGERBSsurface6(  GMlib::PSurf<T,3> *s, int n1, int n2);
    MyGERBSsurface6( const MyGERBSsurface6<T>& copy );
    virtual ~MyGERBSsurface6();

    // Public local functions



    //****************************************
    //****** Virtual public functions   ******
    //****************************************

    // from PCurve
    bool                isClosedU() const override;
    bool                isClosedV() const override;

protected:
    // Virtual function from PCurve that has to be implemented locally
    void                eval( T u, T v, int d1, int d2, bool lu = true, bool lv = true ) const override;

    T                   getStartPV() const override;
    T                   getEndPV()   const override;

    T                   getStartPU() const override;
    T                   getEndPU()   const override;

    //void                localSimulate(double dt) override;


    // Protected data for the curve

    GMlib::DMatrix<GMlib::PSurf<T,3>*> _S; //local curves
    GMlib::DVector<T>           _u; //knot vector
    GMlib::DVector<T>           _v; //knot vector
    int                  _d; //degree
    T                    _su;
    T                    _eu;
    T                    _sv;
    T                    _ev;
    bool                 _isclosedU;
    bool                 _isclosedV;
private:

    T                   _W(int i, int d, T t,const GMlib::DVector<T>& knot) const;
    T                   _B(T t) const;
    T                   _BDeriv(T t) const;
    int                 _findIndex(T t,const GMlib::DVector<T>& knot) const;
    void                _makeKnotVectors(GMlib::DVector<T>& t,int n,T start,T end,bool isclosed);
    void                _createLocalSurfaces(GMlib::PSurf<T, 3>* s,int n1,int n2);


}; // END class MyGERBSsurface6

//} // END namepace GMlib

// Include MyGERBSsurface6 class function implementations
#include "MyGERBSsurface6.c"


#endif // GM_MyGERBSsurface6_H
