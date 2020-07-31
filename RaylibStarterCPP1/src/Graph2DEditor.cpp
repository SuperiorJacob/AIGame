#include "Graph2DEditor.h"
#include "Graph2D.h"

Graph2DEditor::Graph2DEditor()
{

}

Graph2DEditor::~Graph2DEditor()
{

}

void Graph2DEditor::Update(float deltaTime)
{
	auto mousePos = GetMousePosition();

	std::vector<Graph2D::Node*> nearbyNodes;
	m_graph->GetNearbyNodes(mousePos, GetNodeRadius(), nearbyNodes);

	for (auto nearbyNode : nearbyNodes)
	{
		float dist = Vector2Distance(mousePos, nearbyNode->data);
		int radius = GetNodeRadius() / 2;

		tooClose = (dist <= GetNodeRadius() / 2);

		if (tooClose)
			break;
	}

	if (IsMouseButtonPressed(0))
	{
		if (!tooClose)
		{
			auto newNode = m_graph->AddNode(mousePos);

			for (auto nearbyNode : nearbyNodes)
			{
				float dist = Vector2Distance(newNode->data, nearbyNode->data);
				m_graph->AddEdge(newNode, nearbyNode, dist);
				m_graph->AddEdge(nearbyNode, newNode, dist);
			}
		}
	}
}

void Graph2DEditor::Draw()
{
	// Draw all connections
	for (auto node : m_graph->GetNodes())
	{
		for (auto connection : node->connections)
		{
			DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, m_nodeLineColour);
		}
	}

	// Draw a "preview" node where the mouse is (lines)
	auto mousePos = GetMousePosition();

	std::vector<Graph2D::Node*> nearbyNodes;
	m_graph->GetNearbyNodes(mousePos, m_nodeRadius, nearbyNodes);

	for (auto nearbyNode : nearbyNodes)
	{
		DrawLine(mousePos.x, mousePos.y, nearbyNode->data.x, nearbyNode->data.y, !tooClose ? m_nodeLineColour : RED);
	}

	// Draw all nodes
	for (auto node : m_graph->GetNodes())
	{
		DrawCircle(node->data.x, node->data.y, 8, m_nodeColour);
		DrawCircleLines(node->data.x, node->data.y, 8, m_nodeOutlineColour);
	}

	// Draw if found
	for (auto node : m_graph->GetNodes())
	{
		for (auto connection : node->connections)
		{
			if (node->onto == connection.to)
				DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, m_nodeFoundColour);
		}
	}

	for (auto node : m_graph->GetNodes())
	{
		if (node->onto != nullptr)
		{
			DrawCircle(node->data.x, node->data.y, 8, m_nodeFoundColour);
			DrawCircleLines(node->data.x, node->data.y, 8, m_nodeFoundColour);
		}
	}

	// Draw a "preview" node where the mouse is
	DrawCircle(mousePos.x, mousePos.y, 8, m_nodeColour);
}

Graph2D* Graph2DEditor::GetGraph()
{
	return m_graph;
}

void Graph2DEditor::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}

// Config
void Graph2DEditor::SetNodeRadius(int radius)
{
	m_nodeRadius = radius;
}

void Graph2DEditor::SetNodeColour(Color colour)
{
	m_nodeColour = colour;
}

void Graph2DEditor::SetNodeOutlineColour(Color colour)
{
	m_nodeOutlineColour = colour;
}

void Graph2DEditor::SetNodeLineColour(Color colour)
{
	m_nodeLineColour = colour;
}

int Graph2DEditor::GetNodeRadius()
{
	return m_nodeRadius;
}

Color Graph2DEditor::GetNodeColour()
{
	return m_nodeColour;
}

Color Graph2DEditor::GetNodeOutlineColour()
{
	return m_nodeOutlineColour;
}

Color Graph2DEditor::GetNodeLineColour()
{
	return m_nodeLineColour;
}
