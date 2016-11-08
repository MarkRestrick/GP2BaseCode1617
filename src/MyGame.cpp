#include "MyGame.h"

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{
	m_TestObject = nullptr;
}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{

	m_CameraPos = vec3(0, 0, 100);
	
	/*Vertex verts[] = {
		{vec3(-1.0f, -1.0f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,1.0f)},
		{vec3(1.0f, -1.0f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(1.0f,1.0f)},
		{vec3(-1.0f,  1.0f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,0.0f)},
		{vec3(-1.0f, 1.0f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,0.0f)},
		{vec3(1.0f, 1.0f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(1.0f,0.0f)},
		{vec3(1.0f,  -1.0f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(1.0f,1.0f)}
	};
	*/

	int Indices[] =
	{
		0, 2, 1,
		2, 4 , 1
	};

	m_TestObject = new GameObject();
	m_ModelObject = new GameObject();

	string vsPath = ASSET_PATH + SHADER_PATH + "/lightVS.glsl";
	string fsPath = ASSET_PATH + SHADER_PATH + "/lightFS.glsl";
	m_TestObject->loadShaders(vsPath, fsPath);

	//lets load texture
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	m_TestObject->loadTexture(texturePath);

	//m_TestObject->copyVertexData(verts,  6, Indices, 6);
	
	string modPath = ASSET_PATH + MODEL_PATH + "/utah-teapot.fbx";
	m_ModelObject = loadModelFromFile(modPath);
	m_ModelObject->loadShaders(vsPath, fsPath);
	
	
}

void MyGame::destroyScene()
{
	if (m_TestObject)
	{
		m_TestObject->onDestroy();
		delete m_TestObject;
		m_TestObject = nullptr;


	}

	if (m_ModelObject)
	{
		m_ModelObject->onDestroy();
		delete m_ModelObject;
		m_ModelObject = nullptr;
	}
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(m_CameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_ModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -0.2f));

	m_TestObject->onUpdate();
	m_ModelObject->onUpdate();

	m_ModelObject->setCameraPosition(m_CameraPos);
}

void MyGame::render()
{
	GameApplication::render();
	m_TestObject->onRender(m_ViewMatrix, m_ProjMatrix);
	m_ModelObject->onRender(m_ViewMatrix, m_ProjMatrix);
}
