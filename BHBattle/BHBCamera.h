//
//  BHBCamera.h
//  BHBattle
//
//  Created by Martin Beroiz on 4/18/12.
//  Copyright (c) 2012 UTB. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface BHBCamera : NSObject {
    
    float position[3];
    float looksAt[3];
    float upVector[3];
    
}

- (void)translateCameraByX:(float)x Y:(float)y Z:(float)z;
- (void)lookAtX:(float)x Y:(float)y Z:(float)z;
- (void)setUpVectorAtX:(float)x Y:(float)y Z:(float)z;
- (float *)cameraPosition;
- (void)setCameraPositionAtX:(float)x Y:(float)y Z:(float)z;
- (void)loadCameraMatrixInArray: (float *)cameraMatrix;
- (void)attachCameraToModel: (float *)modelMatrix;

@end
