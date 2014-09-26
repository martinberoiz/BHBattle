//
//  Shader.fsh
//  BHBattle
//
//  Created by Martin Beroiz on 4/13/12.
//  Copyright (c) 2012 UTB. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
