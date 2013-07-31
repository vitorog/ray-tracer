#include "gl_renderer.h"

#include <vector>

#include "gl_context.h"

GlRenderer::GlRenderer()
{
}

void GlRenderer::Render()
{
    std::vector<GLfloat> vertices;
    vertices.push_back(-1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);


    GLuint buffer_id;
    glGenBuffers(1,&buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat),&vertices[0],GL_STATIC_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,3);
}
