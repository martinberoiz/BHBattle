//
//  BHBOpenGLView.h
//  BHBattle
//
//  Created by Martin Beroiz on 4/14/12.
//  Copyright (c) 2012 UTB. All rights reserved.
//

#import <UIKit/UIKit.h>
@class CAEAGLLayer;
@class BHBCamera;

@interface BHBOpenGLView : UIView
{
    CAEAGLLayer* _eaglLayer;
    EAGLContext* _context;
    GLuint _colorRenderBuffer;
    GLuint _depthRenderBuffer;
    
    GLuint _positionSlot;
    GLuint _colorSlot;
    GLuint _projectionUniform;
    GLuint _modelViewUniform;
    
    float v1, v2, vcam;
    float x,y,z;
    
    float _currentRotation;
    
    BHBCamera *camera;
    
}

@property(nonatomic,readwrite,retain) EAGLContext *context;

- (void)compileShaders;
- (GLuint)compileShader:(NSString*)shaderName withType:(GLenum)shaderType;
- (void)setupOpenGL;
- (void)setupVBOs;
- (void)render:(CADisplayLink *)displayLink;
- (void)setupDisplayLink;

@end

