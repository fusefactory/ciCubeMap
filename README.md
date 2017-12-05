# ciCubeMap

A [cinder](https://libcinder.org/) block that provides an high-level API for creating and using cubemap (as well as equirectangular) content in various formats.

## Credits

Most, or at least the initial, logic in this block is based on the [DynamicCubeMapping sample application](https://github.com/cinder/Cinder/tree/master/samples/_opengl/DynamicCubeMapping) in the cinder repository.

## Usage
See the example applications in the [samples](https://github.com/fusefactory/ciCubeMap/tree/master/samples) folder, but this is what it more or less looks like;

```c++

#include "ciCubeMap/ciCubeMap.h"

cinder::CubeMap::MapperRef mapperRef;

void CinderApp::setup(){
  // create a cubemapper with an FboCubeMap with faces of 1024x1024 pixels
  mapperRef = cinder::CubeMap::Mapper::create(1024, 1024);
}

void CinderApp::update(){
  // update -render to- the mapper's fbo
  mapperRef->update([this](){
    // call this->drawScene() or something here...
  });
}

void CinderApp::draw(){
  // draw equirectangular representation of cubemap
  gl::drawEquirectangular(mapperRef->getFboCubeMap()->getTextureCubeMap(), Rectf(0,0,400,200));

  // draw cross representation of cubemap
  gl::drawHorizontalCross(mapperRef->getFboCubeMap()->getTextureCubeMap(), Rectf(0,200,400,500));
}
```

![equirectangular](https://github.com/fusefactory/ciCubeMap/blob/gh-pages/equirectangular.png?raw=true)
![horizontalcross](https://github.com/fusefactory/ciCubeMap/blob/gh-pages/horizontalcross.png?raw=true)
