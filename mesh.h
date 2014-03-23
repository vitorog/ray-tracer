#ifndef MESH_H
#define MESH_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

class Mesh
{
public:
    Mesh();
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec2> text_coords_;
    std::vector<int> vertices_index_;
    std::vector<int> normals_index_;
    std::vector<int> text_coords_index_;
};

#endif // MESH_H
