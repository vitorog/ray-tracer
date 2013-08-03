#include "gl_renderer.h"

#include <QImage>
#include <QGLWidget>
#include <vector>

#include "debug.h"
#include "shader_program.h"

GlRenderer::GlRenderer(int width, int height)
{
    width_ = width;
    height_ = height;
}

bool GlRenderer::Initialize()
{
    initialized_ = gl_context_.InitGL();
    if(initialized_){
        shaders_ = new ShaderProgram();
        if(shaders_->CompileShaderFromFile("/media/vitor/Vitor/Development/Projects/Github/RayTracer/basic.vert", kVertexShader)){
            DEBUG_MESSAGE("basic.vert loaded successfully.");
        }else{
            DEBUG_MESSAGE("Failed to load vertex shader.");
        }
        if(shaders_->CompileShaderFromFile("/media/vitor/Vitor/Development/Projects/Github/RayTracer/basic.frag", kFragmentShader)){
            DEBUG_MESSAGE("basic.frag loaded successfully.");
        }else{
            DEBUG_MESSAGE("Failed to load frag shader.");
        }

        float vertices[] = {
            0.0f,0.0f,0.0f,
            (float)width_,0.0f,0.0f,
            0.0f,(float)height_,0.0f,
            (float)width_,0.0f,0.0f,
            (float)width_,(float)height_,0.0f,
            0.0f,(float)height_,0.0f
        };


        float tex_coords[] = {
            0.0f,0.0f,
            1.0f,0.0f,
            0.0f,1.0f,
            1.0f,0.0f,
            1.0f,1.0f,
            0.0f,1.0f
        };

        glViewport(0,0,width_,height_);

        glBindAttribLocation( shaders_->GetHandle(), 0, "vertex_position");
        glBindAttribLocation( shaders_->GetHandle(), 1, "vertex_texture_coords");

        glGenBuffers(2, &vbo_handle_[0]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[0]);
        glBufferData(GL_ARRAY_BUFFER,18*sizeof(float), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[1]);
        glBufferData(GL_ARRAY_BUFFER,12*sizeof(float), tex_coords, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao_handle_);
        glBindVertexArray(vao_handle_);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL );

        glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[1]);
        glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL );

        shaders_->Link();
        shaders_->Use();

        model_matrix_ = glm::mat4(1.0f);
        view_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
        projection_matrix_ = glm::ortho(0.0f,(float)width_, 0.0f, (float)height_);

        model_matrix_location_ = glGetUniformLocation(shaders_->GetHandle(), "model_matrix");
        view_matrix_location_ = glGetUniformLocation(shaders_->GetHandle(), "view_matrix");
        projection_matrix_location_ = glGetUniformLocation(shaders_->GetHandle(), "projection_matrix");
        texture_uniform_location_ = glGetUniformLocation(shaders_->GetHandle(), "texture");

        glActiveTexture(GL_TEXTURE0);
        glUniform1i(texture_uniform_location_, 0);        
    }else{
        DEBUG_MESSAGE("Failed to initialize Gl context.")
    }
    return initialized_;
}


void GlRenderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUniformMatrix4fv(model_matrix_location_, 1, GL_FALSE, &model_matrix_[0][0]);
    glUniformMatrix4fv(view_matrix_location_,1,GL_FALSE,&view_matrix_[0][0]);
    glUniformMatrix4fv(projection_matrix_location_, 1, GL_FALSE, &projection_matrix_[0][0]);
    glBindVertexArray(vao_handle_);
    glDrawArrays(GL_TRIANGLES,0,6);
}

void GlRenderer::Resize(int w, int h)
{
    width_ = w;
    height_= h;
    float vertices[] = {
        0.0f,0.0f,0.0f,
        (float)width_,0.0f,0.0f,
        0.0f,(float)height_,0.0f,
        (float)width_,0.0f,0.0f,
        (float)width_,(float)height_,0.0f,
        0.0f,(float)height_,0.0f
    };
    glViewport(0,0,(float)width_,(float)height_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0,18*sizeof(float), vertices);

    projection_matrix_ = glm::ortho(0.0f,(float)width_, 0.0f, (float)height_);
    view_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
    model_matrix_location_ = glGetUniformLocation(shaders_->GetHandle(), "model_matrix");
}

void GlRenderer::SetTexture(GLubyte *rgba_texture)
{    
    if(texture_id_ != 0){
        glDeleteTextures(1, &texture_id_);
    }
    glGenTextures(1,&texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_,
                 height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void GlRenderer::LoadTextureFromImage(const std::string path)
{
    QImage texture_img = QGLWidget::convertToGLFormat(QImage(QString::fromStdString(path),"JPG"));
    if(texture_id_ != 0){
        glDeleteTextures(1, &texture_id_);
    }
    glGenTextures(1,&texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_img.width(),
                 texture_img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_img.bits());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
