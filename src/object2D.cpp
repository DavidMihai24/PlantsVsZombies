#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // Bottom left
        VertexFormat(corner + glm::vec3(length, 0, 0), color),  // Bottom right
        VertexFormat(corner + glm::vec3(length, length, 0), color), // Top right
        VertexFormat(corner + glm::vec3(0, length, 0), color) // Top left
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateRhombus(
        const std::string& name,
        glm::vec3 leftBottomCorner,
        float sideLength,
        glm::vec3 color,
        bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    glm::vec3 corner2 = corner + glm::vec3(-50, 0, 0);

    // Calculate the height of the rhombus based on the side length
    float height = sideLength * sqrt(3) / 2;

    float rectangleHeight = sideLength / 10;
    float rectangleWidth = sideLength / 3 - 10;

    // Vertices for the rhombus
    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(corner + glm::vec3(sideLength / 2, 0, 1), color),
                    VertexFormat(corner + glm::vec3(sideLength / 4, height / 2, 1), color),
                    VertexFormat(corner + glm::vec3(sideLength / 2, height, 1), color),
                    VertexFormat(corner + glm::vec3(sideLength * 3 / 4, height / 2, 1), color),

                    VertexFormat(corner2 + glm::vec3(sideLength * 3 / 4 - rectangleWidth + 150, height / 2 - rectangleHeight / 2, 1), color),
                    VertexFormat(corner2 + glm::vec3(sideLength * 3 / 4, height / 2 - rectangleHeight / 2, 1), color),
                    VertexFormat(corner2 + glm::vec3(sideLength * 3 / 4, height / 2 + rectangleHeight / 2, 1), color),
                    VertexFormat(corner2 + glm::vec3(sideLength * 3 / 4 - rectangleWidth + 150, height / 2 + rectangleHeight / 2, 1), color)
            };

    Mesh* rhombusWithRectangle = new Mesh(name);

    // Compute the indices for the rhombus and rectangle
    std::vector<unsigned int> indices = {0, 1, 2, 3, 0, 2, 4, 5, 6, 4, 6, 7};


    if (!fill) {
        rhombusWithRectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw triangles for the rhombus and rectangle
        indices.push_back(1);
        indices.push_back(3);
        indices.push_back(5);
        indices.push_back(7);
    }

    rhombusWithRectangle->InitFromData(vertices, indices);
    return rhombusWithRectangle;
}


// Create a hexagon
Mesh* object2D::CreateHexagon(
        const std::string& name,
        glm::vec3 center,
        float sideLength,
        glm::vec3 color,
        bool fill)
{
    std::vector<VertexFormat> vertices;

    // Calculate the coordinates of the hexagon vertices
    for (int i = 0; i < 6; ++i) {
        float angle = i * (2.0f * M_PI) / 6.0f;  // Angle in radians for a regular hexagon
        glm::vec3 vertexPosition = center + glm::vec3(sideLength * cos(angle), sideLength * sin(angle), 2);
        vertices.push_back(VertexFormat(vertexPosition, color));
    }

    Mesh* hexagon = new Mesh(name);
    // Compute the indices for the hexagon
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 1};  // Triangles

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

// create a hexagon with the center at the same coordinates as the hexagon from the previous function
Mesh* object2D::CreateHexagon2(
        const std::string& name,
        glm::vec3 center,
        float sideLength,
        glm::vec3 color,
        bool fill)
{
    std::vector<VertexFormat> vertices;

    // Calculate the coordinates of the hexagon vertices
    for (int i = 0; i < 6; ++i) {
        float angle = i * (2.0f * M_PI) / 6.0f;  // Angle in radians for a regular hexagon
        glm::vec3 vertexPosition = center + glm::vec3(sideLength * cos(angle), sideLength * sin(angle), 1);
        vertices.push_back(VertexFormat(vertexPosition, color));
    }

    Mesh* hexagon = new Mesh(name);
    // Compute the indices for the hexagon
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5};  // Triangles

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

// Create a star
Mesh* object2D::CreateStar(
        const std::string& name,
        glm::vec3 center,
        float sideLength,
        glm::vec3 color,
        bool fill)
{
    std::vector<VertexFormat> vertices;

    for (int i = 0; i < 5; ++i) {
        float outerAngle = glm::radians(i * 144.0f);
        glm::vec3 outerVertexPosition = center + glm::vec3(sideLength * cos(outerAngle), sideLength * sin(outerAngle), 3);
        vertices.push_back(VertexFormat(outerVertexPosition, color));

        float innerAngle = glm::radians(i * 144.0f + 72.0f);
        glm::vec3 innerVertexPosition = center + glm::vec3((sideLength / 3) * cos(innerAngle), (sideLength / 3) * sin(innerAngle), 3);
        vertices.push_back(VertexFormat(innerVertexPosition, color));
    }

    glm::mat3 rotMat = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 0, 1)));
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].position = rotMat * vertices[i].position;
    }

    Mesh* star = new Mesh(name);
    // Indices for the star
    std::vector<unsigned int> indices;
    for (int i = 0; i < 5; ++i) {
        int startIndex = i * 2;

        indices.push_back(startIndex);
        indices.push_back(startIndex + 1);
        indices.push_back((startIndex + 3) % 10);

        indices.push_back(startIndex + 1);
        indices.push_back((startIndex + 3) % 10);
        indices.push_back((startIndex + 2) % 10);

        if (!fill) {
            // Add indices for the outline
            indices.push_back(startIndex);
            indices.push_back((startIndex + 2) % 10);
            indices.push_back((startIndex + 3) % 10);
        }
    }

    /*if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }*/

    star->InitFromData(vertices, indices);
    return star;
}