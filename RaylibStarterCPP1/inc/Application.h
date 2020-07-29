#pragma once

// Forward Declare
class GameObject;

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

	GameObject* m_player1 = nullptr;

};