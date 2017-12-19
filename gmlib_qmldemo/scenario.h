#ifndef SCENARIO_H
#define SCENARIO_H


#include "application/gmlibwrapper.h"

// qt
#include <QObject>


namespace GMlib {

template <typename T, int n>
class PCurve;
template <typename T, int n>
class PSurf;


}
class Scenario : public GMlibWrapper {
  Q_OBJECT

public:
  using GMlibWrapper::GMlibWrapper;

  void    initializeScenario() override;
  void    cleanupScenario() override;

private:
  GMlib::PCurve<float, 3>* mySplineCurve{nullptr};
  GMlib::PCurve<float, 3>* mySplineCurve1{nullptr};
  GMlib::PCurve<float, 3>* mySplineCurve2{nullptr};
  GMlib::PCurve<float, 3>* Curve1{nullptr};
  GMlib::PCurve<float, 3>* Curve2{nullptr};
  GMlib::PCurve<float, 3>* CurveBlend{nullptr};
  GMlib::PCurve<float, 3>* MyBlendCurve{nullptr};
  GMlib::PSurf<float, 3>* MySurface{nullptr};
  GMlib::PSurf<float, 3>* MyERBSurface{nullptr};
  GMlib::PSurf<float, 3>* MyERBSurface1{nullptr};
  GMlib::PSurf<float, 3>* MyERBSurface2{nullptr};
  GMlib::PSurf<float, 3>* MyERBSurface3{nullptr};


public slots:
  void simReplot();

};

#endif // SCENARIO_H
