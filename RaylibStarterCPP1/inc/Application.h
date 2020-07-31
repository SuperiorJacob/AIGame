#pragma once

// Forward Declare
class GameObject;
class Graph2D;
class Graph2DEditor;

class Application 
{
public:

	Application(int windowWidth, int windowHeight, const char *windowTitle);
	~Application();

	void Run();

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Draw();

protected:
private:

	int m_windowWidth;
	int m_windowHeight;
	const char* m_windowTitle;

	//GameObject* m_player1 = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;
	Graph2D* m_graph = nullptr;
};