#include "Application.h"
#include "raylib.h"

#include "GameObject.h"
#include "Player.h"
#include "KeyboardBehaviour.h"

#include "Graph.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"

Application::Application(int windowWidth, int windowHeight, const char* windowTitle) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_windowTitle(windowTitle)
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, m_windowTitle);

	SetTargetFPS(60);

    Load();

    while (!WindowShouldClose())
    {
		float deltaTime = GetFrameTime();
		Update(deltaTime);
		Draw();
    }

    Unload();

	CloseWindow();
}

void Application::Load()
{
	m_graphEditor = new Graph2DEditor();

	m_graph = new Graph2D();

	float spacing = m_graphEditor->GetNodeRadius()/1.5;
	int numRows = m_windowHeight / spacing - 2;
	int numCols = m_windowWidth / spacing - 2;
	//int numRows = 5;
	//int numCols = 5;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			m_graph->AddNode({
				x * spacing + GetRandomValue(m_graphEditor->GetNodeRadius()/2, m_graphEditor->GetNodeRadius()),
				y * spacing + GetRandomValue(m_graphEditor->GetNodeRadius()/2, m_graphEditor->GetNodeRadius())
			});
		}
	}

	for (auto node : m_graph->GetNodes())
	{
		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(node->data, m_graphEditor->GetNodeRadius(), nearbyNodes);

		for (auto connectedNode : nearbyNodes)
		{
			if (connectedNode == node)
				continue;

			float dist = Vector2Distance(node->data, connectedNode->data);
			m_graph->AddEdge(node, connectedNode, dist);
			m_graph->AddEdge(connectedNode, node, dist);
		}
	}

	m_graphEditor->SetGraph(m_graph);

	// Path Finding Test
	Graph2D::PFNode* updateFollow = m_graphEditor->GetGraph()->PathFind(m_graphEditor->GetGraph()->GetNodes().front(), m_graphEditor->GetGraph()->GetNodes().back());
	
	while (updateFollow != nullptr)
	{
		updateFollow->node->onto = updateFollow->parent != nullptr ? updateFollow->parent->node : updateFollow->node;
		updateFollow = updateFollow->parent;
	}
	//
}

void Application::Unload()
{
	delete m_graph;
	m_graph = nullptr;
}

void Application::Update(float deltaTime)
{
	m_graphEditor->Update(deltaTime);
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	
	m_graphEditor->Draw();

	EndDrawing();
}