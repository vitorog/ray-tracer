#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "gl_context.h"


#include "gl_widget.h"

class ShaderProgram;

class GlRenderer
{
public:
    GlRenderer(int width, int height);
    void Render();    
    void Resize(int width,int height);
    void SetTexture(GLubyte *rgba_texture);
    friend class GlWidget; //This is to ensure that only this class will be able to call the Initialize (not really necessary, but anyway...?)
protected:
    //The render can only be initialized after the GL context is created. In this program, created by Qt
    bool Initialize();
private:

    void LoadTextureFromImage(const std::string path);

    //Handles and Ids
    GLuint vao_handle_;
    GLuint vbo_handle_[2];
    GLuint texture_id_;

    ShaderProgram *shaders_;
    //Matrices
    glm::mat4 model_matrix_;
    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;

    //Attributes' location
    GLuint texture_uniform_location_;
    GLuint model_matrix_location_;
    GLuint view_matrix_location_;
    GLuint projection_matrix_location_;


    int width_;
    int height_;
    bool initialized_;
    GLContext gl_context_;
};

#endif // GL_RENDERER_H
