#include "GameHeader/Game.h"
#include "GameHeader/ResourceManager.h"
#include "GameHeader/SpriteRenderer.h"

SpriteRenderer* Renderer;

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader("res/shaders/sprite.vs", "res/shaders/sprite.frag", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("res/textures/background.jpg", GL_FALSE, "background");
    //ResourceManager::LoadTexture("res/textures/awesomeface.png", GL_TRUE, "face");
    // Set render-specific controls
    auto shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);
}

void Game::Update(GLfloat dt)
{
    auto texture = ResourceManager::GetTexture("background");
    Renderer->DrawSprite(texture,
        glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
    );
}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{

}