#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "ciCubeMap/ciCubeMap.h"

using namespace ci;
using namespace ci::app;
using namespace std;

struct Satellite {
  vec3    mPos;
  Colorf  mColor;
};

class DynamicCubeMappingApp : public App {
  public:
  void setup() override;
  void resize() override;
  void update() override;
  void keyDown( KeyEvent event ) override;

  void drawSatellites();
  void drawSkyBox();
  void draw() override;

  gl::TextureCubeMapRef  mSkyBoxCubeMap,mSkyBoxCubeMap2;
  gl::BatchRef      mTeapotBatch, mSkyBoxBatch;
  mat4          mObjectRotation;
  CameraPersp        mCam;
  CubeMap::MapperRef mapperRef;

  bool          mDrawCubeMap;

  std::vector<Satellite>  mSatellites;
  gl::BatchRef      mSatelliteBatch;

  bool bToggle=false;
  bool bSky=true;
  bool bBalls=true;
  bool bTeapot=true;

  bool bSky2=true;
  bool bBalls2=true;

  bool bColored=false;
};

const int SKY_BOX_SIZE = 500;

void DynamicCubeMappingApp::setup()
{
  mSkyBoxCubeMap = gl::TextureCubeMap::create( loadImage( loadAsset( "env_map.jpg" ) ), gl::TextureCubeMap::Format().mipmap() );
  mSkyBoxCubeMap2 = gl::TextureCubeMap::create( loadImage( loadAsset( "env_map_color.jpg" ) ), gl::TextureCubeMap::Format().mipmap() );

#if defined( CINDER_GL_ES )
  auto envMapGlsl = gl::GlslProg::create( loadAsset( "env_map_es2.vert" ), loadAsset( "env_map_es2.frag" ) );
  auto skyBoxGlsl = gl::GlslProg::create( loadAsset( "sky_box_es2.vert" ), loadAsset( "sky_box_es2.frag" ) );
#else
  auto envMapGlsl = gl::GlslProg::create( loadAsset( "env_map.vert" ), loadAsset( "env_map.frag" ) );
  auto skyBoxGlsl = gl::GlslProg::create( loadAsset( "sky_box.vert" ), loadAsset( "sky_box.frag" ) );
#endif

  mTeapotBatch = gl::Batch::create( geom::Teapot().subdivisions( 7 ), envMapGlsl );
  mTeapotBatch->getGlslProg()->uniform( "uCubeMapTex", 0 );

  mSkyBoxBatch = gl::Batch::create( geom::Cube(), skyBoxGlsl );
  mSkyBoxBatch->getGlslProg()->uniform( "uCubeMapTex", 0 );

  // setup satellites (orbiting spheres )
  for( int i = 0; i < 33; ++i ) {
    mSatellites.push_back( Satellite() );
    float angle = i / 33.0f;
    mSatellites.back().mColor = Colorf( CM_HSV, angle, 1.0f, 1.0f );
    mSatellites.back().mPos = vec3( cos( angle * 2 * M_PI ) * 7, 0, sin( angle * 2 * M_PI ) * 7 );
  }
  mSatelliteBatch = gl::Batch::create( geom::Sphere(), getStockShader( gl::ShaderDef().color() ) );

  mDrawCubeMap = true;

  mapperRef = CubeMap::Mapper::create(1024,1024);

  gl::enableDepthRead();
  gl::enableDepthWrite();
}

void DynamicCubeMappingApp::resize()
{
  mCam.setPerspective( 60, getWindowAspectRatio(), 1, 1000 );
}

void DynamicCubeMappingApp::update()
{
  // move the camera semi-randomly around based on time
  mCam.lookAt( vec3( 8 * sin( getElapsedSeconds() / 1 + 10 ), 7 * sin( getElapsedSeconds() / 2 ), 8 * cos( getElapsedSeconds() / 4 + 11 ) ), vec3( 0 ) );

  // rotate the object (teapot) a bit each frame
  mObjectRotation *= rotate( 0.04f, normalize( vec3( 0.1f, 1, 0.1f ) ) );

  // move the satellites
  for( int i = 0; i < 33; ++i ) {
    float angle = i / 33.0f;
    mSatellites[i].mPos = vec3( cos( angle * 2 * M_PI ) * 7, 6 * sin( getElapsedSeconds() * 2 + angle * 4 * M_PI ), sin( angle * 2 * M_PI ) * 7 );
  }
}

void DynamicCubeMappingApp::keyDown( KeyEvent event )
{
  if( event.getChar() == 'd' )
    mDrawCubeMap = ! mDrawCubeMap;

  if( event.getChar() == '/' )
    bToggle = !bToggle;

  if( event.getChar() == 's' )
    bSky = !bSky;

  if( event.getChar() == 'S' )
    bSky2 = !bSky2;

  if( event.getChar() == 't' )
    bTeapot = !bTeapot;

  if( event.getChar() == 'b' )
    bBalls=!bBalls;

  if( event.getChar() == 'B' )
    bBalls2=!bBalls2;

  if(event.getChar() == 'c')
    bColored = !bColored;

  if( event.getChar() == 'e' )
    mapperRef->writeImageEquirectangular("export-equirectangular.png");

  if( event.getChar() == 'E' )
    mapperRef->writeImageHorizontalCross("export-cross.png");

}

void DynamicCubeMappingApp::drawSatellites()
{
  for( const auto &satellite : mSatellites ) {
    gl::pushModelMatrix();
    gl::translate( satellite.mPos );
    gl::color( satellite.mColor );
    mSatelliteBatch->draw();
    gl::popModelMatrix();
  }
}

void DynamicCubeMappingApp::drawSkyBox()
{
  (bColored ? mSkyBoxCubeMap2 : mSkyBoxCubeMap)->bind();
  gl::pushMatrices();
    gl::scale( SKY_BOX_SIZE, SKY_BOX_SIZE, SKY_BOX_SIZE );
    mSkyBoxBatch->draw();
  gl::popMatrices();
}

void DynamicCubeMappingApp::draw()
{
  mapperRef->update([this](){
    gl::clear();

    if(this->bBalls2)
      this->drawSatellites();

    if(this->bSky2)
      this->drawSkyBox();
  });

  gl::clear( Color( 0, 0, 0 ) );
  gl::setMatrices( mCam );

  // now draw the full scene
  if(bBalls)
    drawSatellites();

  if(bSky)
    drawSkyBox();

  if(bTeapot){
    // use cubemapper for teapot reflection
    mapperRef->getFboCubeMap()->bindTexture( 0 );
    gl::pushMatrices();
      gl::multModelMatrix( mObjectRotation );
      gl::scale( vec3( 4 ) );
      mTeapotBatch->draw();
    gl::popMatrices();
  }

  // draw flat preview of cubemap texture
  if( mDrawCubeMap ) {
    gl::setMatricesWindow( getWindowSize() );
    gl::ScopedDepth d( false );
    //gl::drawHorizontalCross( mapperRef->getFboCubeMap()->getTextureCubeMap(), Rectf( 0, 0, 300, 150 ) );

    if(bToggle)
      gl::drawHorizontalCross( mapperRef->getFboCubeMap()->getTextureCubeMap(), Rectf( 0, 0, 300, 150 ) );
    else
      gl::drawEquirectangular( mapperRef->getFboCubeMap()->getTextureCubeMap(), Rectf( 0, getWindowHeight() - 200, 400, getWindowHeight() ) ); // try this alternative
  }
}

CINDER_APP( DynamicCubeMappingApp, RendererGl( RendererGl::Options().msaa( 16 ) ) )
