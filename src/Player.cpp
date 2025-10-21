#include "Player.h"
#include <src/Vector2d.h>
#include <iostream>

void Player::Draw()
{
    //Make 3 vectors for each point in Triangle
    
    Vector2d v1 = {position.Add(direction.Scale(size)).x, position.Add(direction.Scale(size)).y};
    
    Vector2d v2 = {position.Add(direction.Scale(-size)).x, position.Add(direction.Scale(-size)).y};
    
    Vector2d v3 = v2;

    v2.y += (v1.x - position.x)/2;
    v3.y -= (v1.x - position.x)/2;

    DrawRectanglePro({position.x,position.y, size*2, size*2} , {size,size}, angle*180/PI + 45, shipColor);
    //DrawPoly({v1.x,v1.y}, 7, size*1.5f, angle*180/PI, WHITE);
    DrawTriangle({v1.x,v1.y},{v2.x,v2.y}, {v3.x,v3.y} , sailColor);
    DrawTriangle({v2.x,v2.y},{v1.x,v1.y}, {v3.x,v3.y} , sailColor);
    

}

void Player::CheckInput() // May use WASD or Arrow keys
{
    if (IsKeyDown(KEY_UP) | IsKeyDown(KEY_W)) 
    {
        velocity.x += direction.x * acceleration;
        velocity.y += direction.y * acceleration;
    }
		
    else if (IsKeyDown(KEY_DOWN) | IsKeyDown(KEY_S)) //Player accelerates only half as fast backwards
    {
        velocity.x -= direction.x * acceleration / 2;
        velocity.y -= direction.y * acceleration / 2;
    }
    
    if (IsKeyDown(KEY_RIGHT) | IsKeyDown(KEY_D))
    {
        angle += turnSpeed * GetFrameTime();
    }

    if (IsKeyDown(KEY_LEFT) | IsKeyDown(KEY_A))
    {
        angle -= turnSpeed * GetFrameTime();
    }
    
}

void Player::Update()
{
    direction.x = cos(angle);
    direction.y = sin(angle);
    
    //Add offset velocity
    position = position.Add(velocity.Scale(GetFrameTime()));

    //Player loses more speed the faster they're moving. 
    velocity.x -= velocity.x * friction * GetFrameTime();
    velocity.y -= velocity.y * friction * GetFrameTime();

            if (GetScreenWidth() < position.x)
            {
                position.x = 0;
            }
            if (0 > position.x)
            {
                position.x = GetScreenWidth();
            }
            if (GetScreenHeight() < position.y)
            {
                position.y = 0;
            }
            if (0 > position.y)
            {
                position.y = GetScreenHeight();
            }

    windDirection = windDirection.Normalize();
    velocity.x += windDirection.x * windStrength * GetFrameTime();
    velocity.y += windDirection.y * windStrength * GetFrameTime();
    
}
