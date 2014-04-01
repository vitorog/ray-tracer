#include <QApplication>
#include <iostream>
#include <obj_loader.h>

#include "ray_tracer.h"
#include "ray_tracer_scene.h"
#include "mesh_object.h"
#include "sphere.h"

RayTracerScene* CreateScene()
{
    OBJLoader ol;
    std::vector<Object*> objs  = ol.Load("../cornell_box.obj");
    if(!objs.empty()){
        RayTracerScene *s = new RayTracerScene();
        for(int i = 0; i < objs.size(); i++){
            MeshObject *ob = new MeshObject(objs.at(i));
            s->objects_.push_back(ob);
        }
        Camera *c = new Camera(glm::vec3(0.0f,0.0f,3.0f),
                               glm::vec3(0.0f,0.0f,-1.0f),
                               glm::vec3(0.0f,1.0f,0.0f));
        Material m;
        m.ka_ = glm::vec3(0.1,0.1,0.1);
        m.kd_ = glm::vec3(1.0,1.0,1.0);
        m.ks_ = glm::vec3(0.2,0.2,0.2);
        PointLight *l = new PointLight(glm::vec3(0.0f,1.0f,3.0f),m);
        s->light_ = l;
        s->camera_ = c;



        RayTracerObject* sphere = new Sphere(glm::vec3(0.0f,0.0f,0.0f),1.0f);
        s->objects_.push_back(sphere);

        return s;
    }
    return NULL;
}


int main(int argc, char** argv)
{
    //    QApplication app(argc,argv);
    //    RayTracerGUI gui;
    //    gui.show();
    //    return app.exec();

    QApplication app(argc,argv);
    setlocale(LC_NUMERIC,"C");
    RayTracer ray_tracer;
    RayTracerScene *s = CreateScene();
    if(s != NULL){
        ray_tracer.SetScene(s);
    }


    ray_tracer.Initialize();
    ray_tracer.CastRays();
    return app.exec();
}
