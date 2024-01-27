#pragma once

#include "components/simple_scene.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>


namespace m1
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:
        Lab3();
        ~Lab3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float starSpawnTimer = 0.0f;
        float starSpawnInterval = 4.0f;
        float hexagonSpawnTimer = 0.0f;
        float hexagonSpawnInterval = 7.0f;
        glm::mat3 modelMatrix;
        float angularStep;
        int lives = 3;
        bool isDraggingRhombus = false;
        int savedMouseX, savedMouseY;
        int initialSavedMouseX, initialSavedMouseY;
        int numberOfStarsAvailable = 6;
        float rhombusCx, rhombusCy;
        int savedMouseOnBtnX;
        bool rhombusIsSelected = false;
        bool renderRhombusInSquare1 = false, renderRhombusInSquare2 = false, renderRhombusInSquare3 = false,
        renderRhombusInSquare4 = false, renderRhombusInSquare5 = false, renderRhombusInSquare6 = false,
        renderRhombusInSquare7 = false, renderRhombusInSquare8 = false, renderRhombusInSquare9 = false;
        bool square1Occupied = false, square2Occupied = false, square3Occupied = false, square4Occupied = false,
        square5Occupied = false, square6Occupied = false, square7Occupied = false, square8Occupied = false,
        square9Occupied = false;
        int orangeRhombusCx = 150, orangeRhombusCy = 100;
        int blueRhombusCx = 250, blueRhombusCy = 100;
        int yellowRhombusCx = 400, yellowRhombusCy = 100;
        int purpleRhombusCx = 500, purpleRhombusCy = 100;
        bool rhombusToBeRendered1IsOrange = false, rhombusToBeRendered2IsOrange = false, rhombusToBeRendered3IsOrange = false,
        rhombusToBeRendered4IsOrange = false, rhombusToBeRendered5IsOrange = false, rhombusToBeRendered6IsOrange = false,
        rhombusToBeRendered7IsOrange = false, rhombusToBeRendered8IsOrange = false, rhombusToBeRendered9IsOrange = false;
        bool rhombusToBeRendered1IsBlue = false, rhombusToBeRendered2IsBlue = false, rhombusToBeRendered3IsBlue = false,
        rhombusToBeRendered4IsBlue = false, rhombusToBeRendered5IsBlue = false, rhombusToBeRendered6IsBlue = false,
        rhombusToBeRendered7IsBlue = false, rhombusToBeRendered8IsBlue = false, rhombusToBeRendered9IsBlue = false;
        bool rhombusToBeRendered1IsYellow = false, rhombusToBeRendered2IsYellow = false, rhombusToBeRendered3IsYellow = false,
        rhombusToBeRendered4IsYellow = false, rhombusToBeRendered5IsYellow = false, rhombusToBeRendered6IsYellow = false,
        rhombusToBeRendered7IsYellow = false, rhombusToBeRendered8IsYellow = false, rhombusToBeRendered9IsYellow = false;
        bool rhombusToBeRendered1IsPurple = false, rhombusToBeRendered2IsPurple = false, rhombusToBeRendered3IsPurple = false,
        rhombusToBeRendered4IsPurple = false, rhombusToBeRendered5IsPurple = false, rhombusToBeRendered6IsPurple = false,
        rhombusToBeRendered7IsPurple = false, rhombusToBeRendered8IsPurple = false, rhombusToBeRendered9IsPurple = false;
        float orangeStarsSpawnTimer = 0.0f;
        float orangeStarsSpawnInterval = 3.0f;
        float blueStarsSpawnTimer = 0.0f;
        float blueStarsSpawnInterval = 3.0f;
        float yellowStarsSpawnTimer = 0.0f;
        float yellowStarsSpawnInterval = 3.0f;
        float purpleStarsSpawnTimer = 0.0f;
        float purpleStarsSpawnInterval = 3.0f;
        float scaleRhombus = 1.0f;
        float scaleHexagon = 1.0f;

        struct HexagonData {
            // a vector of hexagons with a pair of (hexagonColor, lineToAppear) and a pair of (translateX, hits)
            std::vector<std::pair<std::pair<float, float>, std::pair<float, int>>> hexagons;
        };

        HexagonData hexagonData;

        struct StarData {
            std::vector<std::pair<float, float>> pinkStars;
            // a vector of stars with a pair of (starX, starY) and a float representing (color, translateX)
            std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> orangeStars;
            std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> blueStars;
            std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> yellowStars;
            std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> purpleStars;
        };

        StarData starData;


        struct SquareData {
            bool& renderFlag;
            bool& occupiedFlag;
            bool& rhombusOrangeFlag;
            bool& rhombusBlueFlag;
            bool& rhombusYellowFlag;
            bool& rhombusPurpleFlag;
            int minX, maxX, minY, maxY;
            bool orangeRhombusToBeDeletedOnMousePress, blueRhombusToBeDeletedOnMousePress, yellowRhombusToBeDeletedOnMousePress, purpleRhombusToBeDeletedOnMousePress;
        };

        SquareData squareData[9] = {
                {renderRhombusInSquare1, square1Occupied, rhombusToBeRendered1IsOrange, rhombusToBeRendered1IsBlue,
                        rhombusToBeRendered1IsYellow, rhombusToBeRendered1IsPurple, 125, 235, 585, 695, false, false, false, false},
                {renderRhombusInSquare2, square2Occupied, rhombusToBeRendered2IsOrange, rhombusToBeRendered2IsBlue,
                        rhombusToBeRendered2IsYellow, rhombusToBeRendered2IsPurple, 125, 235, 440, 550, false, false, false, false},
                {renderRhombusInSquare3, square3Occupied, rhombusToBeRendered3IsOrange, rhombusToBeRendered3IsBlue,
                        rhombusToBeRendered3IsYellow, rhombusToBeRendered3IsPurple, 125, 235, 295, 405, false, false, false, false},
                {renderRhombusInSquare4, square4Occupied, rhombusToBeRendered4IsOrange, rhombusToBeRendered4IsBlue,
                        rhombusToBeRendered4IsYellow, rhombusToBeRendered4IsPurple, 270, 380, 585, 695, false, false, false, false},
                {renderRhombusInSquare5, square5Occupied, rhombusToBeRendered5IsOrange, rhombusToBeRendered5IsBlue,
                        rhombusToBeRendered5IsYellow, rhombusToBeRendered5IsPurple, 270, 380, 440, 550, false, false, false, false},
                {renderRhombusInSquare6, square6Occupied, rhombusToBeRendered6IsOrange, rhombusToBeRendered6IsBlue,
                        rhombusToBeRendered6IsYellow, rhombusToBeRendered6IsPurple, 270, 380, 295, 405, false, false, false, false},
                {renderRhombusInSquare7, square7Occupied, rhombusToBeRendered7IsOrange, rhombusToBeRendered7IsBlue,
                        rhombusToBeRendered7IsYellow, rhombusToBeRendered7IsPurple, 415, 525, 585, 695, false, false, false, false},
                {renderRhombusInSquare8, square8Occupied, rhombusToBeRendered8IsOrange, rhombusToBeRendered8IsBlue,
                        rhombusToBeRendered8IsYellow, rhombusToBeRendered8IsPurple, 415, 525, 440, 550, false, false, false, false},
                {renderRhombusInSquare9, square9Occupied, rhombusToBeRendered9IsOrange, rhombusToBeRendered9IsBlue,
                        rhombusToBeRendered9IsYellow, rhombusToBeRendered9IsPurple, 415, 525, 295, 405, false, false, false, false}
        };
    };
}   // namespace m1