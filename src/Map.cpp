#include "Map.hpp"
#include <cmath>
#include <limits>

Map::Map() {
    createMapLayout(800, 600);  // Default size
}

void Map::createMapLayout(int width, int height) {
    walls.clear();  // Clear existing walls

    // Outer Boundaries
    sf::RectangleShape topWall(sf::Vector2f(width, 20));
    topWall.setPosition(0, 0);
    topWall.setFillColor(sf::Color(222, 174, 127));
    walls.push_back(topWall);

    sf::RectangleShape bottomWall(sf::Vector2f(width, 20));
    bottomWall.setPosition(0, height - 20);
    bottomWall.setFillColor(sf::Color(222, 174, 127));
    walls.push_back(bottomWall);

    sf::RectangleShape leftWall(sf::Vector2f(20, height));
    leftWall.setPosition(0, 0);
    leftWall.setFillColor(sf::Color(222, 174, 127));
    walls.push_back(leftWall);

    sf::RectangleShape rightWall(sf::Vector2f(20, height));
    rightWall.setPosition(width - 20, 0);
    rightWall.setFillColor(sf::Color(222, 174, 127));
    walls.push_back(rightWall);


   // Bumps
    sf::RectangleShape bumpLeft(sf::Vector2f(150, 150)); 
    bumpLeft.setPosition(650, height - 170);         
    bumpLeft.setFillColor(sf::Color(222, 174, 127));             
    walls.push_back(bumpLeft);


    sf::RectangleShape bumpRight(sf::Vector2f(150, 150)); 
    bumpRight.setPosition(width - 750, height - 170);        
    bumpRight.setFillColor(sf::Color(222, 174, 127));              
    walls.push_back(bumpRight);

    sf::RectangleShape bump1(sf::Vector2f(150, 66));  
    bump1.setPosition(20, height/2 + 170 );        
    bump1.setFillColor(sf::Color(222, 174, 127));             
    walls.push_back(bump1);

    sf::RectangleShape idk1(sf::Vector2f(10, 90));  
    idk1.setPosition(160, height/2 + 170 + 66 + 100 );         
    idk1.setFillColor(sf::Color(222, 174, 127));              
    walls.push_back(idk1);


    sf::RectangleShape bump2(sf::Vector2f(150, 66));  
    bump2.setPosition(4*width/5 + 215, height/2 - 200 );        
    bump2.setFillColor(sf::Color(222, 174, 127));              
    walls.push_back(bump2);

    sf::RectangleShape idk2(sf::Vector2f(10, 90)); 
    idk2.setPosition(4*width/5 + 215, height/2 - 220 - 66 - 100 );         
    idk2.setFillColor(sf::Color(222, 174, 127));             
    walls.push_back(idk2);





    //cars
    sf::RectangleShape car1(sf::Vector2f(120, 66));  
    car1.setPosition((width-100)/2+10, height - 150);        
    car1.setFillColor(sf::Color(0, 153, 0));              
    walls.push_back(car1);

    sf::RectangleShape car2(sf::Vector2f(66, 120)); 
    car2.setPosition((width-100)/2+40, 100);         
    car2.setFillColor(sf::Color(160, 160, 160));             
    walls.push_back(car2);

    sf::RectangleShape sideWall(sf::Vector2f(10, 80));
    sideWall.setPosition((width)/2-200, 20);
    sideWall.setFillColor(sf::Color::White);
    walls.push_back(sideWall);

    sf::RectangleShape sideWall2(sf::Vector2f(10, 80));
    sideWall2.setPosition((width)/2+200, 20);
    sideWall2.setFillColor(sf::Color::White);
    walls.push_back(sideWall2);


    //  LEFT SIDE HOUSES 
    float xLeft = 300;
    float yLeft = 200;
    float rectWidth = 400;
    float rectHeight = 300;
    float doorHeight = 90;
    float wallThickness = 10;

    // First House (Left Side)
    sf::RectangleShape topWallLeft(sf::Vector2f(rectWidth, wallThickness));
    topWallLeft.setPosition(xLeft, yLeft);
    topWallLeft.setFillColor(sf::Color::White);
    walls.push_back(topWallLeft);

    sf::RectangleShape bottomWallLeft(sf::Vector2f(rectWidth, wallThickness));
    bottomWallLeft.setPosition(xLeft, yLeft + rectHeight);
    bottomWallLeft.setFillColor(sf::Color::White);
    walls.push_back(bottomWallLeft);

    // Left Wall with Doorway
    float leftDoorY = yLeft + 40;
    sf::RectangleShape leftUpper(sf::Vector2f(wallThickness, leftDoorY - yLeft));
    leftUpper.setPosition(xLeft, yLeft);
    leftUpper.setFillColor(sf::Color::White);
    walls.push_back(leftUpper);

    sf::RectangleShape leftLower(sf::Vector2f(wallThickness, rectHeight - (leftDoorY - yLeft + doorHeight)));
    leftLower.setPosition(xLeft, leftDoorY + doorHeight);
    leftLower.setFillColor(sf::Color::White);
    walls.push_back(leftLower);

    // Right Wall with Doorway
    float rightDoorY = yLeft + 80;
    sf::RectangleShape rightUpper(sf::Vector2f(wallThickness, rightDoorY - yLeft));
    rightUpper.setPosition(xLeft + rectWidth, yLeft);
    rightUpper.setFillColor(sf::Color::White);
    walls.push_back(rightUpper);

    sf::RectangleShape rightLower(sf::Vector2f(wallThickness, rectHeight - (rightDoorY - yLeft + doorHeight)+10));
    rightLower.setPosition(xLeft + rectWidth, rightDoorY + doorHeight);
    rightLower.setFillColor(sf::Color::White);
    walls.push_back(rightLower);

    // Lower House (Left Side)
    float lowerXLeft = xLeft + 100;
    float lowerYLeft = yLeft + rectHeight + 10;
    float lowerWidth = 200;
    float lowerHeight = 300;

    sf::RectangleShape bottomWallLowerLeft(sf::Vector2f(lowerWidth, wallThickness));
    bottomWallLowerLeft.setPosition(lowerXLeft, lowerYLeft + lowerHeight);
    bottomWallLowerLeft.setFillColor(sf::Color::White);
    walls.push_back(bottomWallLowerLeft);

    // Left Wall with Doorway
    float lowerLeftDoorY = lowerYLeft + 30;
    sf::RectangleShape lowerLeftUpper(sf::Vector2f(wallThickness, lowerLeftDoorY - lowerYLeft));
    lowerLeftUpper.setPosition(lowerXLeft, lowerYLeft);
    lowerLeftUpper.setFillColor(sf::Color::White);
    walls.push_back(lowerLeftUpper);

    sf::RectangleShape lowerLeftLower(sf::Vector2f(wallThickness, lowerHeight - (lowerLeftDoorY - lowerYLeft + doorHeight)));
    lowerLeftLower.setPosition(lowerXLeft, lowerLeftDoorY + doorHeight);
    lowerLeftLower.setFillColor(sf::Color::White);
    walls.push_back(lowerLeftLower);

    // Right Wall with Doorway
    float lowerRightDoorY = lowerYLeft + 70;
    sf::RectangleShape lowerRightUpper(sf::Vector2f(wallThickness, lowerRightDoorY - lowerYLeft));
    lowerRightUpper.setPosition(lowerXLeft + lowerWidth, lowerYLeft);
    lowerRightUpper.setFillColor(sf::Color::White);
    walls.push_back(lowerRightUpper);

    sf::RectangleShape lowerRightLower(sf::Vector2f(wallThickness, lowerHeight - (lowerRightDoorY - lowerYLeft + doorHeight)+10));
    lowerRightLower.setPosition(lowerXLeft + lowerWidth, lowerRightDoorY + doorHeight);
    lowerRightLower.setFillColor(sf::Color::White);
    walls.push_back(lowerRightLower);

    //  RIGHT SIDE HOUSES (Inverted Orientation)
    float xRight = width - xLeft - rectWidth;
    float yRight = yLeft + rectHeight;  







    // Inverted House (Right Side)
    sf::RectangleShape bottomWallRight(sf::Vector2f(rectWidth, wallThickness));
    bottomWallRight.setPosition(xRight, yRight);
    bottomWallRight.setFillColor(sf::Color::White);
    walls.push_back(bottomWallRight);

    sf::RectangleShape topWallRight(sf::Vector2f(rectWidth, wallThickness));
    topWallRight.setPosition(xRight, yRight + rectHeight);
    topWallRight.setFillColor(sf::Color::White);
    walls.push_back(topWallRight);

    // Left Wall with Doorway (Inverted)
    float rightLeftDoorY = yRight + 80;  // Inverted
    sf::RectangleShape rightLeftUpper(sf::Vector2f(wallThickness, rightLeftDoorY - yRight));
    rightLeftUpper.setPosition(xRight, yRight);
    rightLeftUpper.setFillColor(sf::Color::White);
    walls.push_back(rightLeftUpper);

    sf::RectangleShape rightLeftLower(sf::Vector2f(wallThickness, rectHeight - (rightLeftDoorY - yRight + doorHeight)+10));
    rightLeftLower.setPosition(xRight, rightLeftDoorY + doorHeight);
    rightLeftLower.setFillColor(sf::Color::White);
    walls.push_back(rightLeftLower);

    // Right Wall with Doorway (Inverted)
    float rightRightDoorY = yRight + 30;  // Inverted
    sf::RectangleShape rightRightUpper(sf::Vector2f(wallThickness, rightRightDoorY - yRight));
    rightRightUpper.setPosition(xRight + rectWidth, yRight);
    rightRightUpper.setFillColor(sf::Color::White);
    walls.push_back(rightRightUpper);

    sf::RectangleShape rightRightLower(sf::Vector2f(wallThickness, rectHeight - (rightRightDoorY - yRight + doorHeight)+10));
    rightRightLower.setPosition(xRight + rectWidth, rightRightDoorY + doorHeight);
    rightRightLower.setFillColor(sf::Color::White);
    walls.push_back(rightRightLower);

    // Lower House (Inverted on Right Side)
    float lowerXRight = xRight + 50;
    float lowerYRight = yRight - lowerHeight - 10; 

    sf::RectangleShape bottomWallLowerRight(sf::Vector2f(lowerWidth, wallThickness));
    bottomWallLowerRight.setPosition(lowerXRight, lowerYRight);
    bottomWallLowerRight.setFillColor(sf::Color::White);
    walls.push_back(bottomWallLowerRight);

    // Left Wall with Doorway (Inverted)
    float lowerLeftDoorYRight = lowerYRight + 70;
    sf::RectangleShape lowerLeftUpperRight(sf::Vector2f(wallThickness, lowerLeftDoorYRight - lowerYRight));
    lowerLeftUpperRight.setPosition(lowerXRight, lowerYRight);
    lowerLeftUpperRight.setFillColor(sf::Color::White);
    walls.push_back(lowerLeftUpperRight);

    sf::RectangleShape lowerLeftLowerRight(sf::Vector2f(wallThickness, lowerHeight - (lowerLeftDoorYRight - lowerYRight + doorHeight)+10));
    lowerLeftLowerRight.setPosition(lowerXRight, lowerLeftDoorYRight + doorHeight);
    lowerLeftLowerRight.setFillColor(sf::Color::White);
    walls.push_back(lowerLeftLowerRight);

    // Right Wall with Doorway (Inverted)
    float lowerRightDoorYRight = lowerYRight + 30;
    sf::RectangleShape lowerRightUpperRight(sf::Vector2f(wallThickness, lowerRightDoorYRight - lowerYRight));
    lowerRightUpperRight.setPosition(lowerXRight + lowerWidth, lowerYRight);
    lowerRightUpperRight.setFillColor(sf::Color::White);
    walls.push_back(lowerRightUpperRight);

    sf::RectangleShape lowerRightLowerRight(sf::Vector2f(wallThickness, lowerHeight - (lowerRightDoorYRight - lowerYRight + doorHeight)+10));
    lowerRightLowerRight.setPosition(lowerXRight + lowerWidth, lowerRightDoorYRight + doorHeight);
    lowerRightLowerRight.setFillColor(sf::Color::White);
    walls.push_back(lowerRightLowerRight);





    // Parallel Diagonal Buses in the Middle

    // Bus Dimensions
    float busLength = rectWidth;  
    float busWidth = 70;               
    float busSpacing = 120;             

    // First Bus (Top-left to Bottom-right)
    sf::RectangleShape bus1(sf::Vector2f(busLength, busWidth));
    bus1.setFillColor(sf::Color(204, 204, 0));
    bus1.setOrigin(busLength / 2, busWidth / 2);                    
    bus1.setPosition(width / 2, height / 2 - busSpacing);           
    bus1.setRotation(45);                                           
    walls.push_back(bus1);

    // Second Bus (Parallel to the first one)
    sf::RectangleShape bus2(sf::Vector2f(busLength, busWidth));
    bus2.setFillColor(sf::Color(204, 0, 0));
    bus2.setOrigin(busLength / 2, busWidth / 2);                     
    bus2.setPosition(width / 2, height / 2 + busSpacing);            
    bus2.setRotation(45);                                            
    walls.push_back(bus2);
}

void Map::resize(int windowWidth, int windowHeight) {
    walls.clear();  
    createMapLayout(windowWidth, windowHeight);  // Recreate layout to fit new size
}


void Map::draw(sf::RenderWindow& window) {
    for (auto& wall : walls) {
        window.draw(wall);
    }
}

bool Map::checkCollision(const sf::FloatRect& bounds) const {
    for (const auto& wall : walls) {
        if (wall.getRotation() != 0) {
            if (checkRotatedCollision(wall, bounds)) {
                return true;  // Collision detected with a rotated wall
            }
        } else {
            if (wall.getGlobalBounds().intersects(bounds)) {
                return true;  // Collision with regular (non-rotated) wall
            }
        }
    }
    return false;
}




bool Map::checkRotatedCollision(const sf::RectangleShape& shape, const sf::FloatRect& bounds) const {
    sf::Transform transform = shape.getTransform();
    sf::Vector2f points[4];

    // Get the four corners of the rotated rectangle
    points[0] = transform.transformPoint(0, 0);
    points[1] = transform.transformPoint(shape.getSize().x, 0);
    points[2] = transform.transformPoint(shape.getSize().x, shape.getSize().y);
    points[3] = transform.transformPoint(0, shape.getSize().y);

    return checkSATCollision(points, bounds);
}

bool Map::checkSATCollision(const sf::Vector2f* rectPoints, const sf::FloatRect& bounds) const {
    sf::Vector2f axes[4] = {
        rectPoints[1] - rectPoints[0],  // Edge 1
        rectPoints[2] - rectPoints[1],  // Edge 2
        {1, 0},                         // X-axis for the AABB
        {0, 1}                          // Y-axis for the AABB
    };

    // Normalize axes
    for (auto& axis : axes) {
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        if (length != 0) {
            axis /= length;
        }
    }

    // Project both shapes onto each axis
    for (const auto& axis : axes) {
        float minA = std::numeric_limits<float>::max();
        float maxA = std::numeric_limits<float>::lowest();

        // Project rectangle points
        for (int i = 0; i < 4; ++i) {
            float projection = rectPoints[i].x * axis.x + rectPoints[i].y * axis.y;
            minA = std::min(minA, projection);
            maxA = std::max(maxA, projection);
        }

        // Project AABB (bullet/player)
        sf::Vector2f boundsPoints[4] = {
            {bounds.left, bounds.top},
            {bounds.left + bounds.width, bounds.top},
            {bounds.left + bounds.width, bounds.top + bounds.height},
            {bounds.left, bounds.top + bounds.height}
        };

        float minB = std::numeric_limits<float>::max();
        float maxB = std::numeric_limits<float>::lowest();

        for (int i = 0; i < 4; ++i) {
            float projection = boundsPoints[i].x * axis.x + boundsPoints[i].y * axis.y;
            minB = std::min(minB, projection);
            maxB = std::max(maxB, projection);
        }

        // Check for overlap
        if (maxA < minB || maxB < minA) {
            return false;  // No collision on this axis
        }
    }

    return true;  // Collision detected on all axes
}

sf::Color beige(222, 174, 127);  