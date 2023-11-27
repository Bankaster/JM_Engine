#include "GameObject.h"
#include "Component.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"
#include "ComponentTexture.h"
#include "ComponentMesh.h"
#include <vector>

GameObject::GameObject(std::string name, GameObject* parent)
{
	Name = name;
	Parent = parent;

	//Only Scene Game Object has nullptr as a parent, so dont add a transform to it
	if (parent != nullptr)
	{
		transform = new ComponentTransform(this);
		AddComponent(transform);
	}
}

GameObject::~GameObject() {}

void GameObject::Enable() //Start up + bool toggle
{
	this->active = true;
}

void GameObject::Disable()
{
	this->active = false;
}

void GameObject::EnableParent()
{
	this->active = true;
	for (unsigned int i = 0; i < this->children.size(); i++)
	{
		children[i]->EnableParent();
	}
}

void GameObject::DisableParent()
{
	this->active = false;
	for (unsigned int i = 0; i < this->children.size(); i++)
	{
		children[i]->DisableParent();
	}
}

void GameObject::ChangeName(const char* name) 
{
	Name = name;
}

void GameObject::Update() 
{
	if (!components.empty())
	{
		std::vector<Component*>::iterator item = components.begin();
		bool ret = true;

		for (; item != components.end() && ret == true; ++item)
		{
			(*item)->Update();
		}
	}

	//MYTODO: Should this be here? No, Its a little bugged

	//if (ExternalApp->scene->gameObjectSelected != nullptr && ExternalApp->scene->gameObjectSelected != ExternalApp->scene->rootGameObject 
	//	&& !ExternalApp->scene->gameObjectSelected->children.empty())
	//{
	//	//to dont get a kilometer function
	//	GameObject* gameObjectSelected = ExternalApp->scene->gameObjectSelected;
	//	
	//	for (unsigned int i = 0; i < gameObjectSelected->children.size(); i++)
	//	{
	//		if (gameObjectSelected->children[i]->GetComponent(typeComponent::Mesh)->type == typeComponent::Mesh)
	//		{
	//			ComponentTransform* compMesh = (ComponentTransform*)gameObjectSelected->children[i]->GetComponent(typeComponent::Transform);
	//			compMesh->SetTransformMatrix(gameObjectSelected->transform->GetTransformMatrix());
	//		}
	//	}
	//}
}

void GameObject::SetParent(GameObject* parent)
{
	Parent = parent;
}

Component* GameObject::AddComponent(Component* component)
{
	Component* ret = nullptr;

	switch (component->type)
	{
	case(typeComponent::Error):
		//LOG("Component Type Error! Something broke...");
		break;

	case(typeComponent::Transform):
		ret = new ComponentTransform(this);
		LOG("Component Transform added to %s", component->parent->Name.c_str());
		break;

	case(typeComponent::Material):
		if (this->GetComponent(typeComponent::Material) != nullptr) {
			return nullptr;
		}
		ret = new ComponentTexture(this);
		LOG("Component Texture added to %s", component->parent->Name.c_str());
		break;

	case(typeComponent::Mesh):
		ret = new ComponentMesh(this);
		LOG("Component mesh added to %s", component->parent->Name.c_str());
		break;

	case(typeComponent::Camera):
		ret = new ComponentCamera(this);
		LOG("Component Camera added to %s", component->parent->Name.c_str());
		break;
	}

	components.push_back(component);
	return ret;
}

GameObject* GameObject::AddChildren(GameObject* children) 
{
	this->children.push_back(children);
	return children;
}

Component* GameObject::GetComponent(typeComponent type)
{
	std::vector<Component*>::iterator item = components.begin();

	for (; item != components.end(); ++item) 
	{
		if ((*item)->type == type) 
		{
			return (*item);
		}
	}
	return nullptr;
}

std::vector<Component*> GameObject::GetComponents(typeComponent type)
{
	std::vector<Component*>::iterator item = components.begin();

	std::vector<Component*> ret;

	for (; item != components.end(); ++item) 
	{
		if ((*item)->type == type) {
			ret.push_back((*item));
		}
	}

	return ret;
}