//
//  EAGLView.h
//  metaio SDK
//
// Copyright 2007-2013 metaio GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>


@class EAGLContext;



// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface EAGLView : UIView
{    
@private	
    // The pixel dimensions of the CAEAGLLayer.
    GLint framebufferWidth;
    GLint framebufferHeight;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
    GLuint depthRenderbuffer;
    
    BOOL supportAntialiasing;
    
    //Anti-aliasing buffers
    GLuint msaaFramebuffer;
    GLuint msaaRenderBuffer;
    GLuint msaaDepthBuffer;
@public
    GLuint defaultFramebuffer, colorRenderbuffer;
    
}

@property (nonatomic, retain) EAGLContext *context;

- (void)setFramebuffer;
- (BOOL)presentFramebuffer;
- (BOOL)deviceSupportsAntialiasing;


@end
