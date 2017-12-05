#include "cinder/app/App.h"
#include "cinder/Log.h"
#include "cinder/app/RendererGl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/CameraUi.h"
#include "ciCubeMap/ciCubeMap.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define GRIDSIZE 20
#define SPACING 2
#define BLOCKSIZE 1
#define SKY_BOX_SIZE 500.0f

class GridApp : public App {
  public:
  void setup() override;
  void resize() override;
  void update() override;
  void draw() override;
  void drawGrid(double t);
  void drawSkyBox();

  void keyDown( KeyEvent event ) override;

  CubeMap::MapperRef mapperRef, mapperA, mapperB = nullptr;
  CameraPersp cam;
  CameraUi camUi;
  gl::BatchRef mSkyBoxBatch;

  unsigned int redraws=0;
  double freezeTime;
};

void GridApp::setup()
{
  mapperRef = CubeMap::Mapper::create(1024,1024);
  mapperA = mapperRef;

  cam.setWorldUp(vec3(0, 1, 0));
  cam.lookAt(vec3(0), vec3(0, 0, 1));
  cam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1, 10000 );

  camUi = CameraUi( &cam, app::App::get()->getWindow() );

  #if defined( CINDER_GL_ES )
    auto skyBoxGlsl = gl::GlslProg::create( loadAsset( "sky_box_es2.vert" ), loadAsset( "sky_box_es2.frag" ) );
  #else
    auto skyBoxGlsl = gl::GlslProg::create( loadAsset( "sky_box.vert" ), loadAsset( "sky_box.frag" ) );
  #endif

  mSkyBoxBatch = gl::Batch::create( geom::Cube(), skyBoxGlsl );
  mSkyBoxBatch->getGlslProg()->uniform( "uCubeMapTex", 0 );
}

void GridApp::resize()
{
  cam.setPerspective( 60, getWindowAspectRatio(), 0.1, 1000 );
}

void GridApp::update()
{
  if(redraws > 0){
    redraws += 1;
    // CI_LOG_I("Redraw " << redraws);

    mapperB->update([this](){
      gl::clear();
      drawSkyBox();
    });

    mapperRef = mapperRef == mapperA ? mapperB : mapperA;
  }
}

void GridApp::keyDown( KeyEvent event )
{
  if( event.getChar() == 'e' )
    mapperRef->writeImageEquirectangular("equirectangular-"+std::to_string(getElapsedFrames())+".png");

  if( event.getChar() == 'E' )
    mapperRef->writeImageHorizontalCross("hcross-"+std::to_string(getElapsedFrames())+".png");

  if(event.getChar() == ' '){
    if(redraws == 0) {

      freezeTime = getElapsedSeconds();
      redraws = 1;

      if(!mapperB)
       mapperB = CubeMap::Mapper::create(1024,1024);

    } else {

      redraws = 0;
      mapperRef = mapperB;
    }
  }
}

void GridApp::draw()
{
  if(redraws == 0){

    double t = getElapsedSeconds();

    // draw grid scene to cubemap
    mapperRef->update([this, t](){
      gl::clear();
      this->drawGrid(t);
    });

    // draw skybox with cubemap texture
    gl::clear( Color( 0, 0, 0 ) );
    gl::setMatrices( cam );
    drawSkyBox();

  } else {

    // draw skybox with cubemap texture
    gl::clear( Color( 0, 0, 0 ) );
    gl::setMatrices( cam );
    drawSkyBox();

    // draw equirectangular preview
    gl::setMatricesWindow( getWindowSize() );
    gl::ScopedDepth d( false );
    gl::drawEquirectangular(mapperRef->getFboCubeMap()->getTextureCubeMap(), Rectf(0,0,400,200));
  }
}

void GridApp::drawGrid(double t){
  gl::color(ci::ColorA(1,1,1,0.5f));

  for(int iz=0; iz<GRIDSIZE; iz++){
  for(int ix=0; ix<GRIDSIZE; ix++){
    float x = ((GRIDSIZE-1) * -0.5f + ix) * SPACING;
    float z = ((GRIDSIZE-1) * -0.5f + iz) * SPACING;
    float y = std::sin(t + std::sqrt(x*x+z*z) * 0.2f) * 1.5f;

    gl::drawCube(vec3(x,y,z), vec3(BLOCKSIZE));
  }}
}

void GridApp::drawSkyBox(){
  mapperRef->getFboCubeMap()->getTextureCubeMap()->bind();
  gl::pushMatrices();
    gl::scale( SKY_BOX_SIZE, SKY_BOX_SIZE, SKY_BOX_SIZE );
    mSkyBoxBatch->draw();
  gl::popMatrices();
}

CINDER_APP( GridApp, RendererGl( RendererGl::Options().msaa( 16 ) ) )
