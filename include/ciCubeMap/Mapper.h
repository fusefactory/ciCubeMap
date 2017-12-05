#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Signals.h"

namespace cinder { namespace CubeMap {

  class Mapper;
  using MapperRef=std::shared_ptr<Mapper>;

  class Mapper {
    public:

      Mapper(ci::gl::FboCubeMapRef fbo) : mFbo(fbo){
      }

      void update(std::function<void(void)> drawFunc=nullptr);

      inline ci::gl::FboCubeMapRef getFboCubeMap() {
        return mFbo;
      }

      ci::gl::FboRef createHorizontalCrossFbo(bool render=true);
      ci::gl::FboRef createEquirectangularFbo(bool render=true);

      void updateHorizontalCrossFbo(ci::gl::FboRef fbo);
      void updateEquirectangularFbo(ci::gl::FboRef fbo);

      void writeImageHorizontalCross(const ci::fs::path &path);
      void writeImageEquirectangular(const ci::fs::path &path);

    public: // static factory methods

      static MapperRef create(){
        return create(1024,1024);
      }

      static MapperRef create(int width, int height){
        return std::make_shared<Mapper>(ci::gl::FboCubeMap::create( width, height ));
      }

      static MapperRef create(int width, int height, const ci::gl::FboCubeMap::Format &format){
        return std::make_shared<Mapper>(ci::gl::FboCubeMap::create( width, height, format ));
      }

    public:
      ci::signals::Signal<void()> drawSignal;

    private:
      ci::gl::FboCubeMapRef    mFbo;
  }; // class Mapper
}} // namespace cinder::CubeMap
