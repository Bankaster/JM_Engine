#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "ModuleEditor.h"
#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"
#include "Glew/include/glew.h"
#include "LoadFBX.h"

//todo: REMOVE this before 1st delivery!!
#include "glmath.h"

#define MAX_LIGHTS 8

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

	float3 CalculateFaceNormal(const float3& vertex1, const float3& vertex2, const float3& vertex3);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	CPlane Grid;

	std::vector<LoadFBX> Models;
	bool modelLoaded = false;
	const char* myModelPath;

	//You won't need this after using Frustum
	mat4x4 ProjectionMatrix;
	uint VBO;
	uint EBO;
	uint VAO;
};