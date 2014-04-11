#include <QApplication>
#include <iostream>
#include <obj_loader.h>

#include "ray_tracer_gui.h"
#include "ray_tracer.h"
#include "ray_tracer_scene.h"
#include "mesh_object.h"
#include "sphere.h"
#include "plane.h"

RayTracerScene* CreateScene()
{
    OBJLoader ol;
    std::vector<Object*> objs  = ol.Load("../cornell_box.obj");
    if(!objs.empty()){
        RayTracerScene *s = new RayTracerScene();
        for(int i = 0; i < objs.size(); i++){
            MeshObject *ob = new MeshObject(objs.at(i));
            //            s->objects_.push_back(ob);
        }
        Camera *c = new Camera(glm::vec3(0.0f,0.0f,1.0f),
                               glm::vec3(0.0f,0.0f,-1.0f),
                               glm::vec3(0.0f,1.0f,0.0f));
        Material m;
        m.ka_ = glm::vec3(0.1,0.1,0.1);
        m.kd_ = glm::vec3(1.0,1.0,1.0);
        m.ks_ = glm::vec3(0.2,0.2,0.2);
        PointLight *l = new PointLight(glm::vec3(1.0f,1.0f,2.0f),m);
        s->light_ = l;
        s->camera_ = c;



        //        RayTracerObject* sphere = new Sphere(glm::vec3(-1.0f,0.0f,-0.5f),0.5f);
        //        sphere->material_->illum_ = 3;
        //        sphere->material_->kd_ = glm::vec3(0.0f,0.0f,1.0f);
        //        s->objects_.push_back(sphere);

        RayTracerObject* sphere2 = new Sphere(glm::vec3(0.0f,0.0f,-1.0f),0.5f);
        sphere2->material_->kd_ = glm::vec3(0.8f,0.1f,0.1f);
        sphere2->material_->illum_ = 3;
        s->objects_.push_back(sphere2);


        RayTracerObject* ground = new Plane(glm::vec3(0.0f,-2.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
        //        ground->material_->kd_ = glm::vec3(0.2,0.8,0.2);

        RayTracerObject* ceil = new Plane(glm::vec3(0.0f,2.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f));
        RayTracerObject* left_wall = new Plane(glm::vec3(-2.0f,0.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f));
        RayTracerObject* right_wall = new Plane(glm::vec3(2.0f,0.0f,0.0f),glm::vec3(-1.0f,0.0f,0.0f));
        RayTracerObject* back_wall = new Plane(glm::vec3(0.0f,0.0f,-2.0f),glm::vec3(0.0f,0.0f,1.0f));

        left_wall->material_->kd_ = glm::vec3(0.2f,0.8f,0.2f);
        left_wall->material_->illum_ = 3;
        right_wall->material_->kd_ = glm::vec3(0.8f,0.2f,0.2f);


        s->objects_.push_back(ground);
        //        s->objects_.push_back(ceil);
        //        s->objects_.push_back(left_wall);
        //        s->objects_.push_back(right_wall);
        //        s->objects_.push_back(back_wall);
        return s;
    }
    return NULL;
}


int main(int argc, char** argv)
{
    QApplication app(argc,argv);
    RayTracerGUI gui;
    gui.show();
    return app.exec();

    //    QApplication app(argc,argv);
    //    setlocale(LC_NUMERIC,"C");
    //    RayTracer ray_tracer;
    //    RayTracerScene *s = CreateScene();
    //    if(s != NULL){
    //        ray_tracer.SetScene(s);
    //    }


    //    ray_tracer.Initialize();
    //    ray_tracer.CastRays();
    //    return app.exec();
}
