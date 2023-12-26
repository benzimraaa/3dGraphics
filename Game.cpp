#include "Game.h"
#include <iostream>


Game::Game(int width, int height) : 
    gfx(width, height), cube() ,
    lt(LinearTransformation::identity())  
    
{
    cube.shiftZ(3);
    auto rotX = LinearTransformation::RotationX(0.0100);
    auto rotY = LinearTransformation::RotationY(0.00);
    auto rotZ = LinearTransformation::RotationZ(0.0500);
    lt = rotX * rotY * rotZ;
}

void Game::handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            updateModel(event);
            
        }
}


void Game::handleMouseHover(const SDL_MouseMotionEvent& motionEvent) {
    
    // Vec3<int> p1(motionEvent.x, motionEvent.y);
    // Vec3<int> p2(100, 100);
    // gfx.clear();
    // gfx.drawLine(p1, p2);
    // gfx.render();
    
}

void Game::handleMouseClick(int x, int y)
{
    // Vec3<int> p1(x, y);
    // gfx.clear();
    // Star star(15, 100, -200, p1);
    // gfx.drawPolygon(star.getpoints(), Color(255, 0, 0));
    // gfx.drawEllipse(p1, 200, 200, Color(255, 250, 0));
}

void Game::updateModel(SDL_Event event)
{   
    auto isKeyPressed = [](SDL_Scancode key) {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        return state[key];
    };
    const int speed = 10;
    if (isKeyPressed(SDL_SCANCODE_RIGHT)) {
        auto lt = LinearTransformation::RotationZ(0.1);
        cube.transform(lt);
    } 
    if (isKeyPressed(SDL_SCANCODE_LEFT)) {
        auto lt = LinearTransformation::RotationY(0.1);
        cube.transform(lt);
    } 
    if (isKeyPressed(SDL_SCANCODE_UP)) {
        auto lt = LinearTransformation::RotationX(0.1);
        cube.transform(lt);
    } 
    if (isKeyPressed(SDL_SCANCODE_DOWN)) {
    } 
    if (isKeyPressed(SDL_SCANCODE_PAGEUP)){
        cube.shiftZ(0.5);
    } 
    if (isKeyPressed(SDL_SCANCODE_PAGEDOWN)){
        cube.shiftZ(-0.5);

    } 
    if (event.type == SDL_MOUSEWHEEL){
        if (event.wheel.y > 0){
        }
        else if (event.wheel.y < 0){
        }
    } 
    if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == SDL_BUTTON_LEFT){
            isDragging = true;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP){
        if (event.button.button == SDL_BUTTON_LEFT){
            isDragging = false;
        }
    }
    if (isDragging){
    }

}

void Game::run() {
    // Game loop
    quit = false;
    while (!quit) {
        // updateModel();
        // Present the renderer
        handleEvents();
        composeFrame();
        gfx.render();
    }
}

void Game::composeFrame()
{   
    // handleMouseClick(300, 300);
    gfx.clear();
    // draw axes
    cube.transform(lt);
    for (auto& edge : cube.edges)
    {
        gfx.drawLine(cube.vertices[edge.first], cube.vertices[edge.second], Color(0, 0, 255));
        
    }
    // put pixel at each vertex in different color
    // list of 8 colors
    std::vector<Color> colors = {Color(255, 0, 0), Color(0, 255, 0), 
                                 Color(0, 0, 255), Color(255, 255, 0), 
                                 Color(255, 0, 255), Color(0, 255, 255), 
                                 Color(255, 255, 255), Color(150, 100, 0)};
    for (auto& vertex : cube.vertices)
    {
        auto v = vertex.homogeneous();
        v = gfx.screenTransformation(v);
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8 ; ++j)
            {
                gfx.putPixel(v.x+i, v.y+j, colors[&vertex - &cube.vertices[0]]);
            }
        }
    }
    // gfx.drawLine(Vec3<int>(-10000, 0), Vec3<int>(10000, 0), Color(255, 255, 100));
    // gfx.drawLine(Vec3<int>(0, -10000), Vec3<int>(0, 10000), Color(255, 255, 100));
    
}
