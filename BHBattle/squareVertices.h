typedef struct {
    float Position[3];
    float Color[4];
} Vertex;

const Vertex Vertices[] = {
    {{1, -1, 1}, {1, 0, 0, 1}},
    {{1, 1, 1}, {0.75, 0.5, 0, 1}},
    {{-1, 1, 1}, {1., 0.5, 0, 1}},
    {{-1, -1, 1}, {0, 1, 0, 1}},
    {{1, -1, -1}, {0, 1, 1, 1}},
    {{1, 1, -1}, {0, 0, 1, 1}},
    {{-1, 1, -1}, {1, 1, 0, 1}},
    {{-1, -1, -1}, {1, 0, 1, 1}}
};

const GLubyte Indices[] = {
    // Front
    0, 1, 2,
    2, 3, 0,
    // Back
    4, 6, 5,
    4, 7, 6,
    // Left
    2, 7, 3,
    7, 6, 2,
    // Right
    0, 4, 1,
    4, 1, 5,
    // Top
    6, 2, 1, 
    1, 6, 5,
    // Bottom
    0, 3, 7,
    0, 7, 4    
};