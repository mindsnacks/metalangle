//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef LIBANGLE_RENDERER_METAL_DISPLAYMTL_H_
#define LIBANGLE_RENDERER_METAL_DISPLAYMTL_H_

#include "libANGLE/renderer/DisplayImpl.h"

namespace egl
{
class Surface;
}

namespace rx
{

class RendererMtl;

class DisplayMtl : public DisplayImpl
{
  public:
    DisplayMtl(const egl::DisplayState &state);
    ~DisplayMtl() override;

    egl::Error initialize(egl::Display *display) override;
    void terminate() override;

    bool testDeviceLost() override;
    egl::Error restoreLostDevice(const egl::Display *display) override;

    std::string getVendorString() const override;

    DeviceImpl *createDevice() override;

    egl::Error waitClient(const gl::Context *context) override;
    egl::Error waitNative(const gl::Context *context, EGLint engine) override;

    SurfaceImpl *createWindowSurface(const egl::SurfaceState &state,
                                     EGLNativeWindowType window,
                                     const egl::AttributeMap &attribs) override;
    SurfaceImpl *createPbufferSurface(const egl::SurfaceState &state,
                                      const egl::AttributeMap &attribs) override;
    SurfaceImpl *createPbufferFromClientBuffer(const egl::SurfaceState &state,
                                               EGLenum buftype,
                                               EGLClientBuffer clientBuffer,
                                               const egl::AttributeMap &attribs) override;
    SurfaceImpl *createPixmapSurface(const egl::SurfaceState &state,
                                     NativePixmapType nativePixmap,
                                     const egl::AttributeMap &attribs) override;

    ImageImpl *createImage(const egl::ImageState &state,
                           const gl::Context *context,
                           EGLenum target,
                           const egl::AttributeMap &attribs) override;

    ContextImpl *createContext(const gl::State &state,
                               gl::ErrorSet *errorSet,
                               const egl::Config *configuration,
                               const gl::Context *shareContext,
                               const egl::AttributeMap &attribs) override;

    StreamProducerImpl *createStreamProducerD3DTexture(egl::Stream::ConsumerType consumerType,
                                                       const egl::AttributeMap &attribs) override;

    gl::Version getMaxSupportedESVersion() const override;
    gl::Version getMaxConformantESVersion() const override;

    EGLSyncImpl *createSync(const egl::AttributeMap &attribs) override;

    egl::Error makeCurrent(egl::Surface *drawSurface,
                           egl::Surface *readSurface,
                           gl::Context *context) override;

    void populateFeatureList(angle::FeatureList *features) override;

    bool isValidNativeWindow(EGLNativeWindowType window) const override;

    egl::ConfigSet generateConfigs() override;

    RendererMtl *getRenderer() { return mRenderer.get(); }

  protected:
    void generateExtensions(egl::DisplayExtensions *outExtensions) const override;
    void generateCaps(egl::Caps *outCaps) const override;

  private:
    virtual egl::Error makeCurrentSurfaceless(gl::Context *context);

    std::unique_ptr<RendererMtl> mRenderer;
};

}  // namespace rx

#endif /* LIBANGLE_RENDERER_METAL_DISPLAYMTL_H_ */