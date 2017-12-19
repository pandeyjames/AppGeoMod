#include "scenario.h"

#include "testtorus.h"
#include "P3dCurve.h"
#include "P3dCurve1.h"
#include "P3dCurve2.h"
#include "PBspline.h"
#include "PBfunction.h"
#include "CurveBlend2.h"
#include "GERBS.h"
#include "GERBSurface.h"
#include "math.h"

//// hidmanager
//#include "hidmanager/defaulthidmanager.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>


// qt
#include <QQuickItem>



void Scenario::initializeScenario() {

    // Insert a light
    GMlib::Point<GLfloat,3> init_light_pos( 2.0, 4.0, 10 );
    GMlib::PointLight *light = new GMlib::PointLight(  GMlib::GMcolor::white(), GMlib::GMcolor::white(),
                                                       GMlib::GMcolor::white(), init_light_pos );
    light->setAttenuation(0.8, 0.002, 0.0008);
    scene()->insertLight( light, false );

    // Insert Sun
    scene()->insertSun();

    // Default camera parameters
    int init_viewport_size = 600;
    GMlib::Point<float,3> init_cam_pos(  0.0f, 0.0f, 0.0f );
    GMlib::Vector<float,3> init_cam_dir( 0.0f, 1.0f, 0.0f );
    GMlib::Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

    // Projection cam
    auto proj_rcpair = createRCPair("Projection");
    proj_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    proj_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
    proj_rcpair.camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
    proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
    scene()->insertCamera( proj_rcpair.camera.get() );
    proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    // Front cam
    auto front_rcpair = createRCPair("Front");
    front_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, -50.0f, 0.0f ), init_cam_dir, init_cam_up );
    front_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
    scene()->insertCamera( front_rcpair.camera.get() );
    front_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    // Side cam
    auto side_rcpair = createRCPair("Side");
    side_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( -50.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ), init_cam_up );
    side_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
    scene()->insertCamera( side_rcpair.camera.get() );
    side_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    // Top cam
    auto top_rcpair = createRCPair("Top");
    top_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, 0.0f, 50.0f ), -init_cam_up, init_cam_dir );
    top_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
    scene()->insertCamera( top_rcpair.camera.get() );
    top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );



    //  //Surface visualizers
    //  //auto surface_visualizer = new GMlib::PSurfNormalsVisualizer<float,3>;

    //  //Surface
    //  auto surface = new TestTorus;
    //  surface->toggleDefaultVisualizer();
    //  surface->insertVisualizer(surface_visualizer);
    //  surface->replot(200,200,1,1);
    //  scene()->insert(surface);

    //  surface->test01();




    //  //Test Surface from PTrianguloidTrefoil
    //  auto testsurf = new GMlib::PTrianguloidTrefoil<float>();
    //  testsurf->toggleDefaultVisualizer();
    //  testsurf->replot(100,100,1,1);
    //  testsurf->setMaterial(GMlib::GMmaterial::emerald());
    //  //this->scene()->insert(testsurf);





    //  //Circle Custom Not GMlib
//      std::string x,y,z,tmin,tmax;
//      x="t*cos(t)";
//      y="t*sin(t)";
//      z="t";
//      tmin = "5";
//      tmax = "10.0f*M_PI";
//    auto testcurv = new P3DCurve<std::string>(x,y,z,tmin,tmax);
//    testcurv->toggleDefaultVisualizer();
//    testcurv->replot(100,0);
//    testcurv->setColor(GMlib::GMcolor::blue());
//    this->scene()->insert(testcurv);





//    auto testcurv1 = new P3DCurve1<float>();
//    testcurv1->toggleDefaultVisualizer();
//    testcurv1->replot(100,0);
//    testcurv1->setColor(GMlib::GMcolor::green());
//    this->scene()->insert(testcurv1);

//    GMlib::DVector<GMlib::Vector<float,3>> c1(2);
//    for (int i=0; i<2; i++){
//        c[i]=testcurv1->getPosition(testcurv1->getParStart()+i*testcurv1->getParDelta()/2);
//    }

//    auto testcurv2 = new P3DCurve2<float>();
//    testcurv2->toggleDefaultVisualizer();
//    testcurv2->replot(100,0);
//    testcurv2->setColor(GMlib::GMcolor::yellow());
//    this->scene()->insert(testcurv2);

//    GMlib::DVector<GMlib::Vector<float,3>> c2(2);
//    for (int i=0; i<2; i++){
//        c[i]=testcurv2->getPosition(testcurv2->getParStart()+i*testcurv2->getParDelta()/2);
//    }

    //check with GMlib Bspline
//    auto testbsp = new GMlib::PBSplineCurve<float>(c,2);
//    testbsp->toggleDefaultVisualizer();
//    testbsp->replot(100,0);
//    testbsp->setColor(GMlib::GMcolor::green());
//    this->scene()->insert(testbsp);




    //Model Curve
    auto testcurv = new P3DCurve<float>();
    testcurv->toggleDefaultVisualizer();
    testcurv->replot(100,0);
    testcurv->setColor(GMlib::GMcolor::black());
    testcurv->translate(GMlib::Vector<float, 3>(10,10,1));
    this->scene()->insert(testcurv);

    GMlib::DVector<GMlib::Vector<float,3>> c(10);
    for (int i=0; i<10; i++){
        c[i]=testcurv->getPosition(testcurv->getParStart()+i*testcurv->getParDelta()/9);
    }

    //Spline curve
    mySplineCurve = new PBspline<float>(c,2);
    mySplineCurve->toggleDefaultVisualizer();
    mySplineCurve->replot(100,0);
    mySplineCurve->setColor(GMlib::GMcolor::red());
    mySplineCurve->translateGlobal(GMlib::Vector<float,3> (-10.0f,0.0f,10.0f));
    scene()->insert(mySplineCurve);

    mySplineCurve1 = new PBspline<float>(c,2,6);
    mySplineCurve1->toggleDefaultVisualizer();
    mySplineCurve1->replot(100,0);
    mySplineCurve1->translateGlobal(GMlib::Vector<float, 3>(10,0,0));
    mySplineCurve1->setColor(GMlib::GMcolor::blue());
    scene()->insert(mySplineCurve1);


    //Task 3
    Curve1 = new P3DCurve<float>();//(mySplineCurve,10);
    Curve1->toggleDefaultVisualizer();
    Curve1->replot(50,0);
    Curve1->setColor(GMlib::GMcolor::yellow());\
    Curve1->translateGlobal(GMlib::Vector<float, 3>(-5,0,0));
    scene()->insert(Curve1);


    Curve2 = new P3DCurve<float>();//(mySplineCurve,10);
    Curve2->toggleDefaultVisualizer();
    Curve2->replot(50,0);
    Curve2->setColor(GMlib::GMcolor::green());
    Curve2->translateGlobal(GMlib::Vector<float, 3>(-15,0,0));
    Curve2->rotate(90,GMlib::Vector<float, 3>(1,0,0));
    scene()->insert(Curve2);

    CurveBlend = new CurveBlend2<float>(Curve1,Curve2,0.7);
    CurveBlend->toggleDefaultVisualizer();
    CurveBlend->replot(100,0);
    CurveBlend->setColor(GMlib::GMcolor::red());
    scene()->insert(CurveBlend);
    //CurveBlend->translate(GMlib::Vector<float, 3>(10,0,0));

    auto testcurv2 = new P3DCurve1<float>();
    testcurv2->toggleDefaultVisualizer();
    testcurv2->replot(100,0);
    testcurv2->setColor(GMlib::GMcolor::black());
    this->scene()->insert(testcurv2);

    GMlib::DVector<GMlib::Vector<float,3>> d(10);
    for (int i=0; i<10; i++){
        d[i]=testcurv2->getPosition(testcurv2->getParStart()+i*testcurv2->getParDelta()/9);
    }

    //Task 4
    MyBlendCurve = new GERBS<float>(testcurv2,8);
    MyBlendCurve->toggleDefaultVisualizer();
    MyBlendCurve->replot(100,0);
    MyBlendCurve->setColor(GMlib::GMcolor::brown());
    MyBlendCurve->translateGlobal(GMlib::Vector<float,3> (10.0f,0.0f,10.0f));
    scene()->insert(MyBlendCurve);


    //Task 5 Open
    MySurface = new GMlib::PPlane<float>(
                GMlib::Point<float, 3> (0.0f,0.0f,0.f),
                GMlib::Vector<float, 3>(14.0f,5.0f,0.f),
                GMlib::Vector<float, 3>(0.0f,-7.0f,0.0f));
    auto normalVis = new GMlib::PSurfNormalsVisualizer<float,3>();
    MySurface->toggleDefaultVisualizer();
    MySurface->insertVisualizer(normalVis);
    MySurface->replot(100,100,1,1);
    MySurface->setMaterial(GMlib::Material(1,0,0));
    MySurface->translateGlobal(GMlib::Vector<float,3> (10.0f,0.0f,0.0f));
    scene()->insert(MySurface);

    MyERBSurface = new GERBSURFACE<float>(MySurface,10,10);
    MyERBSurface->toggleDefaultVisualizer();
    MyERBSurface->replot(100,100,1,1);
    MyERBSurface->setColor(GMlib::GMcolor::brown());
    MyERBSurface->translateGlobal(GMlib::Vector<float,3> (10.0f,0.0f,10.0f));
    scene()->insert(MyERBSurface);

    //Closed

    auto MyTorus = new GMlib::PTorus<float>(5,2);
//    auto MySphere = new GMlib::PSphere<float>(5);
    auto apple      = new GMlib::PSphere<float>(10);
    auto MyCylinder = new GMlib::PCylinder<float>(2,5);

    MyERBSurface2 = new GERBSURFACE<float>(MyTorus,4,5);
    auto normalVis2 = new GMlib::PSurfNormalsVisualizer<float,3>();
    MyERBSurface2->toggleDefaultVisualizer();
    MyERBSurface2->insertVisualizer(normalVis2);
    MyERBSurface2->replot(50,50,1,1);
    MyERBSurface2->setMaterial(GMlib::GMmaterial::chrome());
    MyERBSurface2->translateGlobal(GMlib::Vector<float,3> (5.0f,0.0f,10.0f));
    scene()->insert(MyERBSurface2);


    MyERBSurface1 = new GERBSURFACE<float>(MyCylinder,4,5);
    auto normalVis1 = new GMlib::PSurfNormalsVisualizer<float,3>();
    MyERBSurface1->toggleDefaultVisualizer();
    MyERBSurface1->insertVisualizer(normalVis1);
    MyERBSurface1->replot(50,50,1,1);
    MyERBSurface1->setMaterial(GMlib::GMmaterial::emerald());
    MyERBSurface1->translateGlobal(GMlib::Vector<float,3> (5.0f,0.0f,-10.0f));
    scene()->insert(MyERBSurface1);



    MyERBSurface3 = new GERBSURFACE<float>(apple,4,5);
    MyERBSurface3->toggleDefaultVisualizer();
    MyERBSurface3->replot(50,50,1,1);
    MyERBSurface3->setMaterial(GMlib::GMmaterial::gold());
    MyERBSurface3->translateGlobal(GMlib::Vector<float,3> (5.0f,0.0f,-10.0f));
    scene()->insert(MyERBSurface3);



    //  //Circle
    //  GMlib::PCircle<float>* testsurf1 = new GMlib::PCircle<float>();
    //  testsurf1->toggleDefaultVisualizer();
    //  testsurf1->replot(100,0);
    //  testsurf1->setColor(GMlib::GMcolor::black());
    //  this->scene()->insert(testsurf1);



    //  //ARC
    //  GMlib::PArc<float>* testsurf = new GMlib::PArc<float>(1,0.5);
    //  testsurf->toggleDefaultVisualizer();
    //  testsurf->replot(50,0);
    //  testsurf->setMaterial(GMlib::GMmaterial::emerald());
    //  this->scene()->insert(testsurf);




}

void Scenario::cleanupScenario() {

}

void Scenario::simReplot()
{
 if (mySplineCurve){
     //mySplineCurve->rotateGlobal(GMlib::Angle(0.1),GMlib::Vector<float,3> (0,1.0f,0.0f));
     mySplineCurve->replot();
 }
 if (mySplineCurve2){
     //mySplineCurve->rotateGlobal(GMlib::Angle(0.1),GMlib::Vector<float,3> (0,1.0f,0.0f));
     mySplineCurve2->replot();
     mySplineCurve2->setCollapsed(true);
 }
 if (Curve1)
     Curve1->replot();
     //Curve1->setCollapsed(true);
 if (Curve2)
     Curve2->replot();
 if (CurveBlend)
     CurveBlend->replot();
 if (MyBlendCurve)
     MyBlendCurve->replot();
 if (MySurface)
     MySurface->replot(10,10,1,1);
 if (MyERBSurface)
     MyERBSurface->replot(10,10,1,1);
 if (MyERBSurface1){
     MyERBSurface1->replot(100,100,1,1);
 }
 if (MyERBSurface2)
     MyERBSurface->replot(10,10,1,1);
 if (MyERBSurface3){
     MyERBSurface1->replot(100,100,1,1);
 }
}
