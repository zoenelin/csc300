#include "graph.h"

Graph::Graph(int maxV)
{
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;

    adjMatrix = new int*[maxVertices]; // pointer of rows
    // each int* stores a row
    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i] = new int[maxVertices]; // create a new row (array of ints)
        for(int j = 0; j < maxVertices; j++)
            adjMatrix[i][j] = 0;
    }

    visited = new bool[maxVertices] {false};    
}

Graph::~Graph()
{
    delete[] visited;

    for(int i = 0; i < maxVertices; i++)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;

    vertex* tempVertex;
    while (vertices) 
    {
        edge* tempEdge;
        // free the memory of the neighbor list of that vertex
        while(vertices->aHead)
        {
            tempEdge = vertices->aHead;
            vertices->aHead = vertices->aHead->eNext;
            delete tempEdge;
        }
        // free that vertex itself
        tempVertex = vertices;
        vertices = vertices->vNext;
        delete tempVertex;

    }
}

void Graph::addVertex(char data)
{
    if(numVertices >= maxVertices)
    {
        cout << "Max number of vertices reached!" << endl;
        return;
    }

    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->vNext = vertices;
    newVertex->aHead = nullptr;
    newVertex->visited = 0;
    vertices = newVertex;

    numVertices++;
}

void Graph::addEdge(char src, char dest, int weight)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    // find src and dest vertices
    while(srcVertex && srcVertex->data != src)
    {
        srcVertex = srcVertex->vNext;
    }
    while(destVertex && destVertex->data != dest)
    {
        destVertex = destVertex->vNext;
    }

    if(!srcVertex || !destVertex)
    {
        cout << "Vertices not found - can't add an edge" << endl;
        return;
    }

    // Adj list - undirected graph
    edge* newEdge = new edge;
    newEdge->dest = destVertex;
    newEdge->weight = weight;
    newEdge->eNext = srcVertex->aHead;
    srcVertex->aHead = newEdge;

    // Since undirected, add the reverse edge as well
    newEdge = new edge;
    newEdge->dest = srcVertex;
    newEdge->weight = weight;
    newEdge->eNext = destVertex->aHead;
    destVertex->aHead = newEdge;

    // Adj Matrix
    int srcIndex = srcVertex->data - 'A';
    int destIndex = destVertex->data - 'A';
    adjMatrix[srcIndex][destIndex] = weight;
    adjMatrix[destIndex][srcIndex] = weight;
}

void Graph::removeVertex(char data)
{
    // find the vertex
    vertex* temp = vertices;
    vertex* prev = nullptr;

    while(temp && temp->data != data)
    {
        prev = temp;
        temp = temp->vNext;
    }
    
    if(!temp)
    {
        cout << "Vertex not found - can't remove" << endl;
        return;
    }

    // remove that vertex from the adj list of all other vertices
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        edge* e = v->aHead;
        edge* prevEdge = nullptr;
        while(e)
        {
            if(e->dest->data == data)
            {
                if(prevEdge)
                    prevEdge->eNext = e->eNext;
                else
                    v->aHead = e->eNext;
                delete e;
                break;
            }
            prevEdge = e;
            e = e->eNext;
        }
    }

    // remove the vertex
    if(prev)
        prev->vNext = temp->vNext;
    else
        vertices = temp->vNext;

    delete temp;

    // Adj matrix
    int index = temp->data - 'A';
    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i][index] = 0;
        adjMatrix[index][i] = 0;
    }

    numVertices--;
}

void Graph::displayAdjList()
{
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        cout << v->data << " -> ";
        for(edge* e = v->aHead; e != nullptr; e = e->eNext)
        {
            cout << e->dest->data << " (" << e->weight << ") -> ";
        }
        cout << "null" << endl;
    }
    cout << endl;
}

void Graph::displayAdjMatrix()
{
    cout << "     ";
    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " "; // column headers
    }
    cout << endl;
    cout << "   ";
    
    for(int i = 0; i < maxVertices; i++)
    {
        cout << "-----";
    }
    cout << endl;

    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " |"; // row header
        for(int j = 0; j < maxVertices; j++)
        {
            cout << setw(3) << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::bfsL(char start)
{
    for(int i = 0; i < maxVertices; i++)
        visited[i] = false;

    // find the start vertex
    vertex* startVertex = vertices;
    while(startVertex && startVertex->data != start)
        startVertex = startVertex->vNext;

    if(!startVertex)
    {
        cout << "Start vertex not found - can't traverse" << endl;
        return;
    }

    // initialize queue for bfs
    node* queue = nullptr;
    enqueue(queue, start); 
    visited[startVertex->data - 'A'] = true;

    cout << "BFS traversal Adjacency List : ";
    while (queue)
    {
        // dequeue the front
        char currentData = queue->data;
        dequeue(queue);
        cout << currentData << " ";

        // find the vertex corresponding to the dequeued element
        vertex* currentVertex = vertices;
        while(currentVertex && currentVertex->data != currentData)
            currentVertex = currentVertex->vNext;

        // add all its neighbors to the queue
        for(edge* e = currentVertex->aHead; e != nullptr; e = e->eNext)
        {
            if(!visited[e->dest->data - 'A'])
            {
                enqueue(queue, e->dest->data);
                visited[e->dest->data - 'A'] = true;
            }
        }
    }
    cout << endl; 
}

// Task 1: Implement removeEdge() function
void Graph::removeEdge(char src, char dest)
{
    // find the source and destination vertices
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    // traverse to the source vertex
    while (srcVertex && srcVertex->data != src)
    {
        srcVertex = srcVertex->vNext;
    }
    // traverse to the destination vertex
    while (destVertex && destVertex->data != dest)
    {
        destVertex = destVertex->vNext;
    }
  
    // check both source and destination vertices 
    if (!srcVertex || !destVertex)
    {
        cout << "Vertex not found - can't delete" << endl;
        return;
    }

    // remove source vertex edge
    edge* prevEdge = nullptr;
    edge* currentEdge = srcVertex->aHead;

    while (currentEdge)
    {
        if (currentEdge->dest == destVertex)
        {
            if (prevEdge)
            {
                prevEdge->eNext = currentEdge->eNext;
            }
            else
            {
                srcVertex->aHead = currentEdge->eNext;
            }
            delete currentEdge;
            break;
        }
        prevEdge = currentEdge;
        currentEdge = currentEdge->eNext;
    }

    // remove the destination vertex edge
    prevEdge = nullptr;
    currentEdge = destVertex->aHead;
    while (currentEdge)
    {
        if (currentEdge->dest == srcVertex)
        {
            if (prevEdge)
            {
                prevEdge->eNext = currentEdge->eNext;
            }
            else
            {
                destVertex->aHead = currentEdge->eNext;
            }
            delete currentEdge;
            break;
        }
        prevEdge = currentEdge;
        currentEdge = currentEdge->eNext;
    }

    // update adjacency matrix
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';
    adjMatrix[srcIndex][destIndex] = 0;
    adjMatrix[destIndex][srcIndex] = 0;
}

// Task 2: Implement bfsM() function - queue
void Graph::bfsM(char start)
{
    for (int i = 0; i < maxVertices; i++)
    {
        visited[i] = false;
    }

    int startIndex = start - 'A';
    
    node* queue = nullptr;
    enqueue(queue, startIndex);
    visited[startIndex] = true;

    cout << "BFS traversal Adjacency Matrix: ";


    // uses queue for BFS traversal
    while (queue)
    {
        int currentIndex = queue->data;
        dequeue(queue);

        cout << char('A' + currentIndex) << " ";

        for (int i = 0; i < maxVertices; i++)
        {
            if (adjMatrix[currentIndex][i] != 0 && !visited[i])
            {
                enqueue(queue, i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

// Task 3: Implement dfsL() function - stack
void Graph::dfsL(char start)
{
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        v->visited = false;
    }

    vertex* startVertex = vertices;
    while (startVertex && startVertex->data != start)
    {
        startVertex = startVertex->vNext;
    }

    node* stack = nullptr;
    push(stack, startVertex->data - 'A');

    cout << "DFS traversal Adjacency List: ";

    // uses stack for DFS traversal
    while (stack)
    {
        int currentIndex = stack->data;
        pop(stack);

        vertex* currentVertex = vertices;
        while (currentVertex && (currentVertex->data - 'A') != currentIndex)
        {
            currentVertex = currentVertex->vNext;
        }

        // check if visited or not 
        if (currentVertex || !currentVertex->visited)
        {
            currentVertex->visited = true;
            cout << currentVertex->data << " ";

            // push unvisited vertices to stack
            edge* e = currentVertex->aHead;
            while (e)
            {
                if (!e->dest->visited)
                {
                    push(stack, e->dest->data - 'A');
                }
                e = e->eNext;
            }
        }
    }
    cout << endl;
}

// Task 4: Implement dfsM() function - stack
void Graph::dfsM(char start)
{
    for (int i = 0; i < maxVertices; i++)
    {
        visited[i] = false;
    }

    int startIndex = start - 'A';
    
    node* stack = nullptr;
    push(stack, startIndex);

    cout << "DFS traversal Adjacency Matrix: ";

    // uses stack for DFS traversal
    while (stack)
    {
        int currentIndex = stack->data;
        pop(stack);

        // check if visited or not 
        if (!visited[currentIndex])
        {
            visited[currentIndex] = true;
            cout << char('A' + currentIndex) << " ";

            // push unvisited vertices to stack
            for (int i = maxVertices - 1; i >= 0; i--)
            {
                if (adjMatrix[currentIndex][i] != 0 && !visited[i])
                {
                    push(stack, i);
                }
            }
        }
    }
    cout << endl;
}