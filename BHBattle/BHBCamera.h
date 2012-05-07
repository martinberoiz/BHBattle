//
//  BHBCamera.h
//  BHBattle
//
//  Created by Martin Beroiz on 4/18/12.
//  Copyright (c) 2012 UTB. All rights reserved.
//

#import <Foundation/Foundation.h>


 /*typedef union { 
     struct { 
         float x, y, z;
     }; 
     float v[3]; 
 } __attribute__((aligned(3))) vector3D;*/


@interface BHBCamera : NSObject {
    
    float fieldOfView;
    float position[3];
    float looksAt[3];
    float upVector[3];
    //float cameraMatrix[16];
    
}

@property(readwrite,nonatomic) float fieldOfView;

- (void)translateCameraByX:(float)x Y:(float)y Z:(float)z;
//- (void)rotateCameraBy:(float)degAngle aroundVector:(float *)vector;
- (void)lookAt:(float)x Y:(float)y Z:(float)z;
- (void)setUpVectorX:(float)x Y:(float)y Z:(float)z;

- (float *)cameraPosition;
- (void)setCameraPositionAtX:(float)x Y:(float)y Z:(float)z;
- (void)loadCameraMatrixInArray: (float *)cameraMatrix;
- (void)attachCameraToModel: (float *)modelMatrix;

@end
