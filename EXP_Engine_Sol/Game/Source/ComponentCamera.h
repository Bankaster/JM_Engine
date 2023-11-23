#pragma once
#include "Component.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleInput.h"

#include "Globals.h"
#include <string>

#include "../External/MathGeoLib/include/MathGeoLib.h"
#include "../External/MathGeoLib/include/Math/float4x4.h"
#include "../External/MathGeoLib/include/Geometry/Frustum.h"
#include "../External/MathGeoLib/include/Math/float3.h"
#include "../External/MathGeoLib/include/Geometry/LineSegment.h"

class ComponentCamera : public Component {
	//Properties
public:

	Frustum frustum;

	bool activeCamera;
	bool frustumCulling;
	bool drawBoundingBoxes;

private:
	bool looking;
	float3 looking_at;

	LineSegment latest_ray;

public:
	void Enable() override;
	void Update() override;
	void Disable() override;
	void DrawInspector() override;

	float GetVerticalFOV() const;
	float GetHorizontalFOV() const;
	void SetFOV(float fov);
	void SetVerticalFOV(float fov);
	void SetHorizontalFOV(float fov);

	void UpdatePos(float3 newPos);
	float3 GetPos() const;

	void SetPos(float3 xyz);
	void SetPos(float x, float y, float z);

	void SetFront(float3 front);
	void SetUp(float3 up);

	float GetAspectRatio() const;
	void SetAspectRatio(float AspectRatio);

	float GetNearPlane() const;
	void SetNearPlane(float distance);

	float GetFarPlane() const;
	void SetFarPlane(float distance);

	void DrawFrustumCube() const;

	float* GetRawViewMatrix();
	float4x4 GetViewMatrix();
	float* GetProjectionMatrix();

	float3 GetFront();
	float3 GetUp();
	float3 GetRight();

	void Look(float3& reference);
	void Match(ComponentCamera* reference);

	void Pan(float3& newPos, float speed, float dt);
	void Orbit(float3& point, float speed, float dt);
	void Zoom(float3& newPos, float speed);
	void LookAt(float3& Spot);
	void Move(float3& newPos, float speed);
	void Rotate(float dt);

	void Focus(float3& center, float distance);

	ComponentCamera(GameObject* parent);
private:

};