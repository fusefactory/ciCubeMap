#include "cinder/ImageIo.h"
#include "ciCubeMap/Mapper.h"

using namespace ci;
using namespace ci::CubeMap;


void Mapper::update(std::function<void(void)> drawFunc){
  // when update is called without drawFunc; it will default to emitting the drawSignal
  if(!drawFunc){
    drawFunc = [this](){ drawSignal.emit(); };
  }

  gl::pushViewport( ivec2( 0, 0 ), mFbo->getSize() );
  // we need to save the current FBO because we'll be calling bindFramebufferFace() below
  gl::context()->pushFramebuffer();
  for( uint8_t dir = 0; dir < 6; ++dir ) {
    gl::setProjectionMatrix( ci::CameraPersp( mFbo->getWidth(), mFbo->getHeight(), 90.0f, 1, 1000 ).getProjectionMatrix() );
    gl::setViewMatrix( mFbo->calcViewMatrix( GL_TEXTURE_CUBE_MAP_POSITIVE_X + dir, vec3( 0 ) ) );
    mFbo->bindFramebufferFace( GL_TEXTURE_CUBE_MAP_POSITIVE_X + dir );

    drawFunc();
  }
  // restore the FBO before we bound the various faces of the CubeMapFbo
  gl::context()->popFramebuffer();
  gl::popViewport();
}

gl::FboRef Mapper::createEquirectangularFbo(bool render){
  auto fbo = gl::Fbo::create(mFbo->getWidth()*4, mFbo->getHeight()*2);

  if(render)
    this->updateEquirectangularFbo(fbo);

  return fbo;
}

gl::FboRef Mapper::createHorizontalCrossFbo(bool render){
  auto fbo = gl::Fbo::create(mFbo->getWidth()*4, mFbo->getHeight()*3);

  if(render)
    this->updateHorizontalCrossFbo(fbo);

  return fbo;
}

void Mapper::updateHorizontalCrossFbo(gl::FboRef fbo){
  gl::ScopedFramebuffer fbScp(fbo);
  gl::ScopedDepth d( false );
  gl::pushViewport( ivec2( 0, 0 ), fbo->getSize() );

  // we need to save the current FBO because we'll
  // be calling bindFramebufferFace() below
  // gl::context()->pushFramebuffer();
  gl::setMatricesWindow( fbo->getWidth(), fbo->getHeight() );

  gl::clear(ColorA(0,0,0,0));
  gl::drawHorizontalCross( mFbo->getTextureCubeMap(), Rectf( 0, 0, fbo->getWidth(), fbo->getHeight() ) ); // try this alternative

  // restore the FBO before we bound the various faces of the CubeMapFbo
  // gl::context()->popFramebuffer();
  gl::popViewport();
}

void Mapper::updateEquirectangularFbo(gl::FboRef fbo){
  gl::ScopedFramebuffer fbScp(fbo);
  gl::pushViewport( ivec2( 0, 0 ), fbo->getSize() );
  // we need to save the current FBO because we'll be calling bindFramebufferFace() below
  // gl::context()->pushFramebuffer();

  gl::setMatricesWindow( fbo->getWidth(), fbo->getHeight() );
  gl::ScopedDepth d( false );

  gl::drawEquirectangular( mFbo->getTextureCubeMap(), Rectf( 0, 0, fbo->getWidth(), fbo->getHeight() ) ); // try this alternative

  // restore the FBO before we bound the various faces of the CubeMapFbo
  // gl::context()->popFramebuffer();
  gl::popViewport();
}

void Mapper::writeImageHorizontalCross(const fs::path &path){
  auto fbo = this->createHorizontalCrossFbo(true);
  writeImage( writeFile(path), fbo->getColorTexture()->createSource() );
}

void Mapper::writeImageEquirectangular(const fs::path &path){
  auto fbo = this->createEquirectangularFbo(true);
  writeImage( writeFile(path), fbo->getColorTexture()->createSource() );
}
