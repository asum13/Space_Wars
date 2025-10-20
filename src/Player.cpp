#include "Player.h"
#include <src/Vector2d.h>
#include <iostream>

void Player::Draw()
{
    //Make 3 vectors for each point in Triangle
    //
		
    Vector2d v1 = {position.Add(direction.Scale(size)).x, position.Add(direction.Scale(size)).y};
    Vector2d v2 = {position.Add(direction.Scale(-size)).x, position.Add(direction.Scale(-size)).y};
    v2.y += abs(v1.x - position.x)/2;
    Vector2d v3 = {position.Add(direction.Scale(-size)).x, position.Add(direction.Scale(-size)).y};
    v3.y -= abs(v1.x - position.x)/2;
    DrawTriangleLines({v1.x,v1.y},{v2.x,v2.y}, {v3.x,v3.y} , color);
}

void Player::CheckInput() // May use WASD or Arrow keys
{
    if (IsKeyDown(KEY_UP)) //Player accelerates twice as fast in the direction they're facing
    {
        velocity.x += direction.x * acceleration;
        velocity.y += direction.y * acceleration;
    }
		
    else if (IsKeyDown(KEY_DOWN)) 
    {
        velocity.x -= direction.x * acceleration / 2;
        velocity.y -= direction.y * acceleration / 2;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        angle -= turnSpeed * GetFrameTime();
        direction.x = cos(angle);
        direction.y = sin(angle);
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        angle += turnSpeed * GetFrameTime();
        direction.x = cos(angle);
        direction.y = sin(angle);
    }
}

void Player::Update()
{
    //Add offset velocity
    position = position.Add(velocity.Scale(GetFrameTime()));

    //Player more speed the faster they're moving. Creates a max 
    velocity.x -= velocity.x * friction * GetFrameTime();
    velocity.y -= velocity.y * friction * GetFrameTime();
}
