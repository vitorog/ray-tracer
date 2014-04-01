#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

class Object;

#include "ray_tracer_object.h"

class MeshObject : public RayTracerObject
{
public:
    MeshObject(Object*);
    void CheckCollision(Ray&);
    Object* obj_;
};

#endif // MESH_OBJECT_H
