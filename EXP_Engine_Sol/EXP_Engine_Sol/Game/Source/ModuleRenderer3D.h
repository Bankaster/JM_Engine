#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "ModuleEditor.h"
#include "GameObject.h"
#include "../External/MathGeoLib/include/MathGeoLib.h"
#include "../External/MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"
#include "../External/Glew/include/glew.h"

//todo: REMOVE this before 1st delivery!!
#include "glmath.h"

#define MAX_LIGHTS 8
#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);
	void BindVBO();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	CPlane Grid;

	GameObject* gameObject = nullptr;
	GameObject* selectedGameObject = nullptr;
	std::vector<GameObject*> gameObjects;

	bool modelLoaded = false;
	const char* myModelPath;

	GLuint checkersTexture;
	GLuint checkerID;
	GLuint texWidth, texHeight;
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

	//You won't need this after using Frustum
	mat4x4 ProjectionMatrix;
	uint VBO;
	uint EBO;
	uint VAO;
};