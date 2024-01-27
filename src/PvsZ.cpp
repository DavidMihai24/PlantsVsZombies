#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <cstdlib>


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float) resolution.x, 0, (float) resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    scaleRhombus = 1.0f;

    rhombusCx = corner.x + squareSide / 2;
    rhombusCy = corner.y + squareSide / 2;

    // Initialize angularStep
    angularStep = 0;

    Mesh *redSquare = object2D::CreateSquare("redSquare", corner, squareSide + 30, glm::vec3(1, 0, 0), true);
    AddMeshToList(redSquare);

    Mesh *greenSquare = object2D::CreateSquare("greenSquare", corner, squareSide * 2 + 20, glm::vec3(0, 1, 0), true);
    AddMeshToList(greenSquare);

    Mesh *whiteSquare = object2D::CreateSquare("whiteSquare", corner, squareSide * 2 - 20, glm::vec3(1, 1, 1), false);
    AddMeshToList(whiteSquare);

    // Create a new mesh - a rectangle
    Mesh *rectangle = object2D::CreateRectangle("rectangle", corner, squareSide + 60, squareSide * 8,glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);

    // Create a new mesh - an orange rhombus
    Mesh *orangeRhombus = object2D::CreateRhombus("orangeRhombus", corner, squareSide * 2, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(orangeRhombus);

    // Create a new mesh - a blue rhombus
    Mesh *blueRhombus = object2D::CreateRhombus("blueRhombus", corner, squareSide * 2, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueRhombus);

    // Create a new mesh - a yellow rhombus
    Mesh *yellowRhombus = object2D::CreateRhombus("yellowRhombus", corner, squareSide * 2, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowRhombus);

    // Create a new mesh - a purple rhombus
    Mesh *purpleRhombus = object2D::CreateRhombus("purpleRhombus", corner, squareSide * 2, glm::vec3(0.5, 0, 0.5), true);
    AddMeshToList(purpleRhombus);

    // Create a new mesh - a turquoise hexagon
    Mesh *innerHexagon = object2D::CreateHexagon("innerHexagon", corner, squareSide / 2, glm::vec3(0.25, 1, 1), true);
    AddMeshToList(innerHexagon);

    // Create a new mesh - a blue hexagon around the turquoise one
    Mesh *blueHexagon = object2D::CreateHexagon2("blueHexagon", corner, squareSide / 3 * 2, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueHexagon);

    // Create a new mesh - an orange hexagon around the turquoise one
    Mesh *orangeHexagon = object2D::CreateHexagon2("orangeHexagon", corner, squareSide / 3 * 2, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(orangeHexagon);

    // Create a new mesh - a yellow hexagon around the turquoise one
    Mesh *yellowHexagon = object2D::CreateHexagon2("yellowHexagon", corner, squareSide / 3 * 2, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowHexagon);

    // Create a new mesh - an orange hexagon around the turquoise one
    Mesh *purpleHexagon = object2D::CreateHexagon2("purpleHexagon", corner, squareSide / 3 * 2, glm::vec3(0.5, 0, 0.5), true);
    AddMeshToList(purpleHexagon);

    Mesh *star = object2D::CreateStar("star", corner, squareSide / 3, glm::vec3(0.5, 0.5, 0.5), true);
    AddMeshToList(star);

    Mesh *pinkStar = object2D::CreateStar("pinkStar", corner, squareSide / 2, glm::vec3(1, 0, 1), true);
    AddMeshToList(pinkStar);

    Mesh *orangeStar = object2D::CreateStar("orangeStar", corner, squareSide / 2, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(orangeStar);

    Mesh *blueStar = object2D::CreateStar("blueStar", corner, squareSide / 2, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueStar);

    Mesh *yellowStar = object2D::CreateStar("yellowStar", corner, squareSide / 2, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowStar);

    Mesh *purpleStar = object2D::CreateStar("purpleStar", corner, squareSide / 2, glm::vec3(0.5, 0, 0.5), true);
    AddMeshToList(purpleStar);
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, 50);

    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 50);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 340);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 630);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(540, 50);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(540, 340);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(540, 630);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(830, 50);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(830, 340);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(830, 630);

    RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(150, 1200);

    RenderMesh2D(meshes["orangeRhombus"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 1200);

    RenderMesh2D(meshes["blueRhombus"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(650, 1200);

    RenderMesh2D(meshes["yellowRhombus"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(900, 1200);

    RenderMesh2D(meshes["purpleRhombus"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(170, 1200);

    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(420, 1200);

    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(670, 1200);

    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(920, 1200);

    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 1150);

    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 1150);

    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(520, 1150);

    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(700, 1150);

    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(770, 1150);

    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(950, 1150);

    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1020, 1150);

    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1090, 1150);

    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    int starPositionX = 1250;

    // render how many resource-stars we have
    for (int i = 0; i < numberOfStarsAvailable; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((float)starPositionX + 70, 1200);

        starPositionX += 70;
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }

    // render the pink stars randomly
    starSpawnTimer += deltaTimeSeconds;
    if (starSpawnTimer > starSpawnInterval) {
        starSpawnTimer = 0.0f;
        float starRandomPositionX = rand() % 2560 + 1;
        float starRandomPositionY = rand() % 1440 + 1;
        starData.pinkStars.push_back(make_pair(starRandomPositionX, starRandomPositionY));
    }
    for (int i = 0; i < starData.pinkStars.size(); i++) {
        RenderMesh2D(meshes["pinkStar"], shaders["VertexColor"], transform2D::Translate(starData.pinkStars[i].first, starData.pinkStars[i].second));
    }

    // make the hexagon vector
    hexagonSpawnTimer += deltaTimeSeconds;
    if (hexagonSpawnTimer > hexagonSpawnInterval) {
        hexagonSpawnTimer = 0.0f;
        int hexagonRandomNumber = rand() % 4 + 1;
        int hexagonRandomLine = rand() % 3 + 1;
        hexagonData.hexagons.push_back(make_pair(make_pair(hexagonRandomNumber, hexagonRandomLine), make_pair(0, 0)));
    }

    // Hexagon movement
    for (int i = 0; i < hexagonData.hexagons.size(); i++) {
        hexagonData.hexagons[i].second.first -= 100 * deltaTimeSeconds;
        float line;
        if (hexagonData.hexagons[i].first.second == 1) {
            line = 160;
        }
        if (hexagonData.hexagons[i].first.second == 2) {
            line = 450;
        }
        if (hexagonData.hexagons[i].first.second == 3) {
            line = 740;
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(2700, line);
        modelMatrix *= transform2D::Translate(hexagonData.hexagons[i].second.first, 0);
        RenderMesh2D(meshes["innerHexagon"], shaders["VertexColor"], modelMatrix);
        if (hexagonData.hexagons[i].first.first == 1) {
            RenderMesh2D(meshes["orangeHexagon"], shaders["VertexColor"], modelMatrix);
        } else if (hexagonData.hexagons[i].first.first == 2) {
            RenderMesh2D(meshes["blueHexagon"], shaders["VertexColor"], modelMatrix);
        } else if (hexagonData.hexagons[i].first.first == 3) {
            RenderMesh2D(meshes["yellowHexagon"], shaders["VertexColor"], modelMatrix);
        } else if (hexagonData.hexagons[i].first.first == 4) {
            RenderMesh2D(meshes["purpleHexagon"], shaders["VertexColor"], modelMatrix);
        }
        if (hexagonData.hexagons[i].second.first <= -2500.0f) {
            lives -= 1;
            hexagonData.hexagons.erase(hexagonData.hexagons.begin() + i);
        }
    }

    if (lives == 0) {
        exit(0);
    }

    for (int i = 1; i <= lives; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((float)1300 + (float)200 * (float)(i - 1), 1250);

        RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);
    }

    // check which rhombus is selected
    if (isDraggingRhombus) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(rhombusCx, rhombusCy);
        if (savedMouseOnBtnX == 170) {
            RenderMesh2D(meshes["orangeRhombus"], shaders["VertexColor"], modelMatrix);
        }
        if (savedMouseOnBtnX == 280) {
            RenderMesh2D(meshes["blueRhombus"], shaders["VertexColor"], modelMatrix);
        }
        if (savedMouseOnBtnX == 390) {
            RenderMesh2D(meshes["yellowRhombus"], shaders["VertexColor"], modelMatrix);
        }
        if (savedMouseOnBtnX == 500) {
            RenderMesh2D(meshes["purpleRhombus"], shaders["VertexColor"], modelMatrix);
        }
    }

    // place rhombuses in squares
    for (int i = 0; i < 9; i++) {
        if (squareData[i].renderFlag) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (float)(i % 3));
            if (squareData[i].occupiedFlag) {
                if (squareData[i].rhombusOrangeFlag) {
                    RenderMesh2D(meshes["orangeRhombus"], shaders["VertexColor"], modelMatrix);
                    squareData[i].occupiedFlag = true;
                } else if (squareData[i].rhombusBlueFlag) {
                    RenderMesh2D(meshes["blueRhombus"], shaders["VertexColor"], modelMatrix);
                    squareData[i].occupiedFlag = true;
                } else if (squareData[i].rhombusYellowFlag) {
                    RenderMesh2D(meshes["yellowRhombus"], shaders["VertexColor"], modelMatrix);
                    squareData[i].occupiedFlag = true;
                } else if (squareData[i].rhombusPurpleFlag) {
                    RenderMesh2D(meshes["purpleRhombus"], shaders["VertexColor"], modelMatrix);
                    squareData[i].occupiedFlag = true;
                }
            }
        }
    }

    // check the 9 squares and see if they are occupied and if so, which rhombus they contain and create the
    // respective stars
    for (int i = 0; i < 9; i++) {
        float starX = 450.0f + 290.0f * (i / 3);
        float starY = 150.0f + 290.0f * (i % 3);
        if (squareData[i].occupiedFlag) {
            orangeStarsSpawnTimer += deltaTimeSeconds;
            if (orangeStarsSpawnTimer > orangeStarsSpawnInterval) {
                orangeStarsSpawnTimer = 0.0f;
                if (squareData[i].rhombusOrangeFlag) {
                    for (int j = 0; j < hexagonData.hexagons.size(); j++) {
                        if (hexagonData.hexagons[j].first.first == 1 && hexagonData.hexagons[j].first.second == (i % 3) + 1) {
                            starData.orangeStars.push_back(make_pair(make_pair(starX, starY), make_pair(1, 0.0f)));
                        }
                    }
                }
            }
            blueStarsSpawnTimer += deltaTimeSeconds;
            if (blueStarsSpawnTimer > blueStarsSpawnInterval) {
                blueStarsSpawnTimer = 0.0f;
                if (squareData[i].rhombusBlueFlag) {
                    for (int j = 0; j < hexagonData.hexagons.size(); j++) {
                        if (hexagonData.hexagons[j].first.first == 2 && hexagonData.hexagons[j].first.second == (i % 3) + 1) {
                            starData.blueStars.push_back(make_pair(make_pair(starX, starY), make_pair(2, 0.0f)));
                        }
                    }
                }
            }
            yellowStarsSpawnTimer += deltaTimeSeconds;
            if (yellowStarsSpawnTimer > yellowStarsSpawnInterval) {
                yellowStarsSpawnTimer = 0.0f;
                if (squareData[i].rhombusYellowFlag) {
                    for (int j = 0; j < hexagonData.hexagons.size(); j++) {
                        if (hexagonData.hexagons[j].first.first == 3 && hexagonData.hexagons[j].first.second == (i % 3) + 1) {
                            starData.yellowStars.push_back(make_pair(make_pair(starX, starY), make_pair(3, 0.0f)));
                        }
                    }
                }
            }
            purpleStarsSpawnTimer += deltaTimeSeconds;
            if (purpleStarsSpawnTimer > purpleStarsSpawnInterval) {
                purpleStarsSpawnTimer = 0.0f;
                if (squareData[i].rhombusPurpleFlag) {
                    for (int j = 0; j < hexagonData.hexagons.size(); j++) {
                        if (hexagonData.hexagons[j].first.first == 4 && hexagonData.hexagons[j].first.second == (i % 3) + 1) {
                            starData.purpleStars.push_back(make_pair(make_pair(starX, starY), make_pair(4, 0.0f)));
                        }
                    }
                }
            }
        }
    }

    // render the stars
    angularStep -= 2 * deltaTimeSeconds;
    for (int i = 0; i < starData.orangeStars.size(); i++) {
        starData.orangeStars[i].second.second += 200 * deltaTimeSeconds;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(starData.orangeStars[i].first.first, starData.orangeStars[i].first.second);
        modelMatrix *= transform2D::Translate(starData.orangeStars[i].second.second, 0);
        modelMatrix *= transform2D::Rotate(angularStep);
        RenderMesh2D(meshes["orangeStar"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < starData.blueStars.size(); i++) {
        starData.blueStars[i].second.second += 200 * deltaTimeSeconds;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(starData.blueStars[i].first.first, starData.blueStars[i].first.second);
        modelMatrix *= transform2D::Translate(starData.blueStars[i].second.second, 0);
        modelMatrix *= transform2D::Rotate(angularStep);
        RenderMesh2D(meshes["blueStar"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < starData.yellowStars.size(); i++) {
        starData.yellowStars[i].second.second += 200 * deltaTimeSeconds;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(starData.yellowStars[i].first.first, starData.yellowStars[i].first.second);
        modelMatrix *= transform2D::Translate(starData.yellowStars[i].second.second, 0);
        modelMatrix *= transform2D::Rotate(angularStep);
        RenderMesh2D(meshes["yellowStar"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < starData.purpleStars.size(); i++) {
        starData.purpleStars[i].second.second += 200 * deltaTimeSeconds;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(starData.purpleStars[i].first.first, starData.purpleStars[i].first.second);
        modelMatrix *= transform2D::Translate(starData.purpleStars[i].second.second, 0);
        modelMatrix *= transform2D::Rotate(angularStep);
        RenderMesh2D(meshes["purpleStar"], shaders["VertexColor"], modelMatrix);
    }

    // when a hexagon reaches a square, the square becomes empty (the rhombus is deleted)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < hexagonData.hexagons.size(); j++) {
            if (hexagonData.hexagons[j].second.first + 2700.0f <= 250.0f + 290.0f * (i / 3) + 200.0f  && hexagonData.hexagons[j].second.first + 2700.0f >= 250.0f + 290.0f * (i / 3) - 100.0f) {
                if ((hexagonData.hexagons[j].first.second == 1 && (i % 3 == 0))
                    || (hexagonData.hexagons[j].first.second == 2 && (i % 3 == 1))
                    || (hexagonData.hexagons[j].first.second == 3 && (i % 3 == 2))) {
                    squareData[i].occupiedFlag = false;
                    if (squareData[i].rhombusOrangeFlag) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(glm::vec3(0, 0, 0).x + 100, glm::vec3(0, 0, 0).y + 100);
                        modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (i % 3));
                        scaleRhombus -= 2.0f * deltaTimeSeconds;
                        modelMatrix *= transform2D::Scale(scaleRhombus, scaleRhombus);
                        modelMatrix *= transform2D::Translate(-(glm::vec3(0, 0, 0).x + 100), -(glm::vec3(0, 0, 0).y + 100));
                        if (scaleRhombus > 0) {
                            RenderMesh2D(meshes["orangeRhombus"], shaders["VertexColor"], modelMatrix);
                        }
                        if (scaleRhombus <= 0) {
                            squareData[i].rhombusOrangeFlag = false;
                            scaleRhombus = 1.0f;
                        }
                    } else if (squareData[i].rhombusBlueFlag) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(glm::vec3(0, 0, 0).x + 100, glm::vec3(0, 0, 0).y + 100);
                        modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (i % 3));
                        scaleRhombus -= 2.0f * deltaTimeSeconds;
                        modelMatrix *= transform2D::Scale(scaleRhombus, scaleRhombus);
                        modelMatrix *= transform2D::Translate(-(glm::vec3(0, 0, 0).x + 100), -(glm::vec3(0, 0, 0).y + 100));
                        if (scaleRhombus > 0) {
                            RenderMesh2D(meshes["blueRhombus"], shaders["VertexColor"], modelMatrix);
                        }
                        if (scaleRhombus <= 0) {
                            squareData[i].rhombusBlueFlag = false;
                            scaleRhombus = 1.0f;
                        }
                    } else if (squareData[i].rhombusYellowFlag) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(glm::vec3(0, 0, 0).x + 100, glm::vec3(0, 0, 0).y + 100);
                        modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (i % 3));
                        scaleRhombus -= 3.0f * deltaTimeSeconds;
                        modelMatrix *= transform2D::Scale(scaleRhombus, scaleRhombus);
                        modelMatrix *= transform2D::Translate(-(glm::vec3(0, 0, 0).x + 100), -(glm::vec3(0, 0, 0).y + 100));
                        if (scaleRhombus > 0) {
                            RenderMesh2D(meshes["yellowRhombus"], shaders["VertexColor"], modelMatrix);
                        }
                        if (scaleRhombus <= 0) {
                            squareData[i].rhombusYellowFlag = false;
                            scaleRhombus = 1.0f;
                        }
                    } else if (squareData[i].rhombusPurpleFlag) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(glm::vec3(0, 0, 0).x + 100, glm::vec3(0, 0, 0).y + 100);
                        modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (i % 3));
                        scaleRhombus -= 3.0f * deltaTimeSeconds;
                        modelMatrix *= transform2D::Scale(scaleRhombus, scaleRhombus);
                        modelMatrix *= transform2D::Translate(-(glm::vec3(0, 0, 0).x + 100), -(glm::vec3(0, 0, 0).y + 100));
                        if (scaleRhombus > 0) {
                            RenderMesh2D(meshes["purpleRhombus"], shaders["VertexColor"], modelMatrix);
                        }
                        if (scaleRhombus <= 0) {
                            squareData[i].rhombusPurpleFlag = false;
                            scaleRhombus = 1.0f;
                        }
                    }
                }
            }
        }
    }

    // when we right-click the mouse on a square with a rhombus, the rhombus is destroyed
    for (int i = 0; i < 9; i++) {
        if (squareData[i].orangeRhombusToBeDeletedOnMousePress) {
            squareData[i].occupiedFlag = false;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(glm::vec3(0, 0, 0).x + 100, glm::vec3(0, 0, 0).y + 100);
            modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (i % 3));
            scaleRhombus -= 2.0f * deltaTimeSeconds;
            modelMatrix *= transform2D::Scale(scaleRhombus, scaleRhombus);
            modelMatrix *= transform2D::Translate(-(glm::vec3(0, 0, 0).x + 100), -(glm::vec3(0, 0, 0).y + 100));
            if (scaleRhombus > 0) {
                RenderMesh2D(meshes["orangeRhombus"], shaders["VertexColor"], modelMatrix);
            }
            if (scaleRhombus <= 0) {
                squareData[i].rhombusOrangeFlag = false;
                scaleRhombus = 1.0f;
                squareData[i].orangeRhombusToBeDeletedOnMousePress = false;
            }
        } else if (squareData[i].blueRhombusToBeDeletedOnMousePress) {
            squareData[i].occupiedFlag = false;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(glm::vec3(0, 0, 0).x + 100, glm::vec3(0, 0, 0).y + 100);
            modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (i % 3));
            scaleRhombus -= 2.0f * deltaTimeSeconds;
            modelMatrix *= transform2D::Scale(scaleRhombus, scaleRhombus);
            modelMatrix *= transform2D::Translate(-(glm::vec3(0, 0, 0).x + 100), -(glm::vec3(0, 0, 0).y + 100));
            if (scaleRhombus > 0) {
                RenderMesh2D(meshes["blueRhombus"], shaders["VertexColor"], modelMatrix);
            }
            if (scaleRhombus <= 0) {
                squareData[i].rhombusBlueFlag = false;
                scaleRhombus = 1.0f;
                squareData[i].blueRhombusToBeDeletedOnMousePress = false;
            }
        } else if (squareData[i].yellowRhombusToBeDeletedOnMousePress) {
            squareData[i].occupiedFlag = false;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(glm::vec3(0, 0, 0).x + 100, glm::vec3(0, 0, 0).y + 100);
            modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (i % 3));
            scaleRhombus -= 3.0f * deltaTimeSeconds;
            modelMatrix *= transform2D::Scale(scaleRhombus, scaleRhombus);
            modelMatrix *= transform2D::Translate(-(glm::vec3(0, 0, 0).x + 100), -(glm::vec3(0, 0, 0).y + 100));
            if (scaleRhombus > 0) {
                RenderMesh2D(meshes["yellowRhombus"], shaders["VertexColor"], modelMatrix);
            }
            if (scaleRhombus <= 0) {
                squareData[i].rhombusYellowFlag = false;
                scaleRhombus = 1.0f;
                squareData[i].yellowRhombusToBeDeletedOnMousePress = false;
            }
        } else if (squareData[i].purpleRhombusToBeDeletedOnMousePress) {
            squareData[i].occupiedFlag = false;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(glm::vec3(0, 0, 0).x + 100, glm::vec3(0, 0, 0).y + 100);
            modelMatrix *= transform2D::Translate(250.0f + 290.0f * (i / 3), 50.0f + 290.0f * (i % 3));
            scaleRhombus -= 3.0f * deltaTimeSeconds;
            modelMatrix *= transform2D::Scale(scaleRhombus, scaleRhombus);
            modelMatrix *= transform2D::Translate(-(glm::vec3(0, 0, 0).x + 100), -(glm::vec3(0, 0, 0).y + 100));
            if (scaleRhombus > 0) {
                RenderMesh2D(meshes["purpleRhombus"], shaders["VertexColor"], modelMatrix);
            }
            if (scaleRhombus <= 0) {
                squareData[i].rhombusPurpleFlag = false;
                scaleRhombus = 1.0f;
                squareData[i].purpleRhombusToBeDeletedOnMousePress = false;
            }
        }
    }

    // detect collisions between stars and hexagons of the same color
    for (int i = 0; i < starData.orangeStars.size(); i++) {
        for (int j = 0; j < hexagonData.hexagons.size(); j++) {
            if (hexagonData.hexagons[j].first.first == 1) {
                if ((starData.orangeStars[i].first.second == 150 && hexagonData.hexagons[j].first.second == 1)
                    || (starData.orangeStars[i].first.second == 440 && hexagonData.hexagons[j].first.second == 2)
                    || (starData.orangeStars[i].first.second == 730 && hexagonData.hexagons[j].first.second == 3)) {
                    if (starData.orangeStars[i].second.second + starData.orangeStars[i].first.first + 100 >= hexagonData.hexagons[j].second.first + 2700) {
                        hexagonData.hexagons[j].second.second += 1;
                        starData.orangeStars.erase(starData.orangeStars.begin() + i);
                        if (hexagonData.hexagons[j].second.second == 3) {
                            hexagonData.hexagons.erase(hexagonData.hexagons.begin() + j);
                            break;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < starData.blueStars.size(); i++) {
        for (int j = 0; j < hexagonData.hexagons.size(); j++) {
            if (hexagonData.hexagons[j].first.first == 2) {
                if ((starData.blueStars[i].first.second == 150 && hexagonData.hexagons[j].first.second == 1)
                    || (starData.blueStars[i].first.second == 440 && hexagonData.hexagons[j].first.second == 2)
                    || (starData.blueStars[i].first.second == 730 && hexagonData.hexagons[j].first.second == 3)) {
                    if (starData.blueStars[i].second.second + starData.blueStars[i].first.first + 100 >= hexagonData.hexagons[j].second.first + 2700) {
                        hexagonData.hexagons[j].second.second += 1;
                        starData.blueStars.erase(starData.blueStars.begin() + i);
                        if (hexagonData.hexagons[j].second.second == 3) {
                            hexagonData.hexagons.erase(hexagonData.hexagons.begin() + j);
                            break;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < starData.yellowStars.size(); i++) {
        for (int j = 0; j < hexagonData.hexagons.size(); j++) {
            if (hexagonData.hexagons[j].first.first == 3) {
                if ((starData.yellowStars[i].first.second == 150 && hexagonData.hexagons[j].first.second == 1)
                    || (starData.yellowStars[i].first.second == 440 && hexagonData.hexagons[j].first.second == 2)
                    || (starData.yellowStars[i].first.second == 730 && hexagonData.hexagons[j].first.second == 3)) {
                    if (starData.yellowStars[i].second.second + starData.yellowStars[i].first.first + 100  >= hexagonData.hexagons[j].second.first + 2700) {
                        hexagonData.hexagons[j].second.second += 1;
                        starData.yellowStars.erase(starData.yellowStars.begin() + i);
                        if (hexagonData.hexagons[j].second.second == 3) {
                            hexagonData.hexagons.erase(hexagonData.hexagons.begin() + j);
                            break;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < starData.purpleStars.size(); i++) {
        for (int j = 0; j < hexagonData.hexagons.size(); j++) {
            if (hexagonData.hexagons[j].first.first == 4) {
                if ((starData.purpleStars[i].first.second == 150 && hexagonData.hexagons[j].first.second == 1)
                    || (starData.purpleStars[i].first.second == 440 && hexagonData.hexagons[j].first.second == 2)
                    || (starData.purpleStars[i].first.second == 730 && hexagonData.hexagons[j].first.second == 3)) {
                    if (starData.purpleStars[i].second.second + starData.purpleStars[i].first.first + 100 >= hexagonData.hexagons[j].second.first + 2700) {
                        hexagonData.hexagons[j].second.second += 1;
                        starData.purpleStars.erase(starData.purpleStars.begin() + i);
                        if (hexagonData.hexagons[j].second.second == 3) {
                            hexagonData.hexagons.erase(hexagonData.hexagons.begin() + j);
                            break;
                        }
                    }
                }
            }
        }
    }
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (isDraggingRhombus) {
        // Compute the new position of the rhombus, based on the mouse position
        rhombusCx += (float)mouseX - (float)savedMouseX;
        rhombusCy += (float)savedMouseY - (float)mouseY;

        savedMouseX = mouseX - deltaX;
        savedMouseY = mouseY - deltaY;

        rhombusIsSelected = true;
    }
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // check if we press the left button of the mouse
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {

        // check if we click on the coordinates of a pink star
        int auxMouseX = mouseX * 2;
        int auxMouseY = 1440 - mouseY * 2;
        for (int i = 0; i < starData.pinkStars.size(); i++) {
            if (auxMouseX >= starData.pinkStars[i].first - 50 && auxMouseX <= starData.pinkStars[i].first + 50 && auxMouseY >= starData.pinkStars[i].second - 50 && auxMouseY <= starData.pinkStars[i].second + 50) {
                starData.pinkStars.erase(starData.pinkStars.begin() + i);
                numberOfStarsAvailable++;
            }
        }

        // check if we press the left button of the mouse on the orange rhombus
        if (mouseX >= 85  && mouseX <= 175 && mouseY >= 30 && mouseY <= 120 && numberOfStarsAvailable >= 1) {
            rhombusCx = 170;
            rhombusCy = 1200;
            savedMouseX = mouseX;
            savedMouseY = mouseY;
            initialSavedMouseX = orangeRhombusCx;
            initialSavedMouseY = orangeRhombusCy;
            savedMouseOnBtnX = 170;
            isDraggingRhombus = true;
        }

        // check if we press the left button of the mouse on the blue rhombus
        if (mouseX >= 210  && mouseX <= 300 && mouseY >= 30 && mouseY <= 120 && numberOfStarsAvailable >= 2) {
            rhombusCx = 420;
            rhombusCy = 1200;
            savedMouseX = mouseX;
            savedMouseY = mouseY;
            initialSavedMouseX = blueRhombusCx;
            initialSavedMouseY = blueRhombusCy;
            savedMouseOnBtnX = 280;
            isDraggingRhombus = true;
        }

        // check if we press the left button of the mouse on the yellow rhombus
        if (mouseX >= 335  && mouseX <= 425 && mouseY >= 30 && mouseY <= 120 && numberOfStarsAvailable >= 2) {
            rhombusCx = 670;
            rhombusCy = 1200;
            savedMouseX = mouseX;
            savedMouseY = mouseY;
            initialSavedMouseX = yellowRhombusCx;
            initialSavedMouseY = yellowRhombusCy;
            savedMouseOnBtnX = 390;
            isDraggingRhombus = true;
        }

        // check if we press the left button of the mouse on the purple rhombus
        if (mouseX >= 460  && mouseX <= 550 && mouseY >= 30 && mouseY <= 120 && numberOfStarsAvailable >= 3) {
            rhombusCx = 920;
            rhombusCy = 1200;
            savedMouseX = mouseX;
            savedMouseY = mouseY;
            initialSavedMouseX = purpleRhombusCx;
            initialSavedMouseY = purpleRhombusCy;
            savedMouseOnBtnX = 500;
            isDraggingRhombus = true;
        }
    }

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        for (int i = 0; i < 9; i++) {
            if (mouseX >= squareData[i].minX && mouseX <= squareData[i].maxX && mouseY >= squareData[i].minY && mouseY <= squareData[i].maxY) {
                if (squareData[i].occupiedFlag) {
                    if (squareData[i].rhombusOrangeFlag) {
                        squareData[i].rhombusOrangeFlag = false;
                        squareData[i].orangeRhombusToBeDeletedOnMousePress = true;
                    }
                    else if (squareData[i].rhombusBlueFlag) {
                        squareData[i].rhombusBlueFlag = false;
                        squareData[i].blueRhombusToBeDeletedOnMousePress = true;
                    }
                    else if (squareData[i].rhombusYellowFlag) {
                        squareData[i].rhombusYellowFlag = false;
                        squareData[i].yellowRhombusToBeDeletedOnMousePress = true;
                    }
                    else if (squareData[i].rhombusPurpleFlag) {
                        squareData[i].rhombusPurpleFlag = false;
                        squareData[i].purpleRhombusToBeDeletedOnMousePress = true;
                    }
                    squareData[i].renderFlag = false;
                    squareData[i].occupiedFlag = false;
                    //squareData[i].rhombusToBeDeletedOnMousePress = true;
                }
            }
        }
    }
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // check if we release the left button of the mouse
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (isDraggingRhombus) {
            // check if we release the left button of the mouse on the squares
            int auxMouseX = mouseX * 2;
            int auxMouseY = 1440 - mouseY * 2;
            for (int i = 0; i < 9; i++) {
                if (mouseX >= squareData[i].minX && mouseX <= squareData[i].maxX && mouseY >= squareData[i].minY && mouseY <= squareData[i].maxY) {
                    if (rhombusIsSelected) {
                        if (!squareData[i].occupiedFlag) {
                            if (initialSavedMouseX == orangeRhombusCx && initialSavedMouseY == orangeRhombusCy) {
                                squareData[i].rhombusOrangeFlag = true;
                                numberOfStarsAvailable -= 1;
                            }
                            else if (initialSavedMouseX == blueRhombusCx && initialSavedMouseY == blueRhombusCy) {
                                squareData[i].rhombusBlueFlag = true;
                                numberOfStarsAvailable -= 2;
                            }
                            else if (initialSavedMouseX == yellowRhombusCx && initialSavedMouseY == yellowRhombusCy) {
                                squareData[i].rhombusYellowFlag = true;
                                numberOfStarsAvailable -= 2;
                            }
                            else if (initialSavedMouseX == purpleRhombusCx && initialSavedMouseY == purpleRhombusCy) {
                                squareData[i].rhombusPurpleFlag = true;
                                numberOfStarsAvailable -= 3;
                            }
                            squareData[i].renderFlag = true;
                            squareData[i].occupiedFlag = true;
                        }
                    }
                }
            }
        }
        isDraggingRhombus = false;
    }
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}