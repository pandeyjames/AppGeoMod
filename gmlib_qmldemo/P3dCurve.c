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



//namespace GMlib {


//*****************************************
// Constructors and destructor           **
//*****************************************

  template <typename T>
  inline
  P3DCurve<T>::P3DCurve( T radius ) {
    _r = radius;
  }

  template <typename T>
  inline
  P3DCurve<T>::P3DCurve( T x, T y, T z, T min, T max ) {
//    _x = x;
//    _y = y;
//    _z = z;
//    tmin = min;
//    tmax = max;
  }

  template <typename T>
  inline
  P3DCurve<T>::P3DCurve( const P3DCurve<T>& copy ) : GMlib::PCurve<T,3>(copy) {}


  template <typename T>
  P3DCurve<T>::~P3DCurve() {}


  //**************************************
  //        Public local functons       **
  //**************************************

  template <typename T>
  inline
  T P3DCurve<T>::getRadius() const {
    return _r;
  }


  template <typename T>
  inline
  void P3DCurve<T>::setRadius( T radius ) {
      _r = radius;
  }


  //***************************************************
  // Overrided (public) virtual functons from PCurve **
  //***************************************************

  template <typename T>
  bool P3DCurve<T>::isClosed() const {
    return true;
  }


  //******************************************************
  // Overrided (protected) virtual functons from PCurve **
  //******************************************************

  template <typename T>
  void P3DCurve<T>::eval( T t, int d, bool /*l*/ ) const {

    this->_p.setDim( d + 1 );
      //_t=t;

    const T ct = 3*cos(t)+cos(t)*cos(6*t);//t * cos(t);
    const T st = 3*sin(t)+sin(t)*cos(6*t);//t * sin(t);

    this->_p[0][0] = ct;
    this->_p[0][1] = st;
    this->_p[0][2] = sin(6*t);//t;
  }


  template <typename T>
  T P3DCurve<T>::getStartP() const {
    //return T(tmin);
      return T(0);
  }

  template <typename T>
  T P3DCurve<T>::parseFunc(T x){
//      typedef double D; // numeric type (float, double, mpfr etc...)

//      typedef exprtk::symbol_table<T> symbol_table_t;
//      typedef exprtk::expression<T>     expression_t;
//      typedef exprtk::parser<T>             parser_t;
//      std::string expression_string = x;

//      D var = _t;

//      symbol_table_t symbol_table;
//      symbol_table.add_variable("t",var);

//      expression_t expression;
//      expression.register_symbol_table(symbol_table);

//      parser_t parser;

//      if (!parser.compile(expression_string,expression))
//      {
//         printf("Compilation error...\n");
//         return;
//      }
//      return expression.value();
  }


  template <typename T>
  T P3DCurve<T>::getEndP()const {
    //return T(tmax);
      return T( M_PI );
  }


//} // END namespace GMlib
