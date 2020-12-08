#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<functional>
#include<math.h>
#include<float.h>
#include<vector>
#include<set>
#include<string.h>
#include<string>
#include<sstream>
using namespace std;
using namespace sf;
#define num 60

vector<pair<int, int>> pathD;
bool sptSet[num][num];
void findmin(float dist[num][num], int& min_x, int& min_y) {
    float mini = FLT_MAX;
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
            if (sptSet[i][j] == false && dist[i][j] < mini) {
                mini = dist[i][j];
                min_x = i;
                min_y = j;
            }
}
void findpath(pair<int, int> previous[num][num], float dist[num][num], int dest_x, int dest_y, int source_x, int source_y) {
    cout << "\nLength of Dijkstra path is: " << dist[dest_x][dest_y] << endl;
    while (previous[dest_x][dest_y].first != source_x || previous[dest_x][dest_y].second != source_y) {        // both simultaneously equal to source coordinates
        cout << "go to ->\n(" << previous[dest_x][dest_y].first << "," << previous[dest_x][dest_y].second << ") ";
        pathD.push_back(make_pair(previous[dest_x][dest_y].first, previous[dest_x][dest_y].second));
        int save_x = dest_x, save_y = dest_y;
        dest_x = previous[save_x][save_y].first;
        dest_y = previous[save_x][save_y].second;
    }
}
void dijkstra(int source_x, int source_y, int dest_x, int dest_y, int grid[num][num]) {
    pair<int, int> previous[num][num];
    float dist[num][num];
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
            dist[i][j] = FLT_MAX;
    dist[source_x][source_y] = 0.0;
    int found = 0;
    for (int i = 0; i < num && found == 0; i++)
        for (int j = 0; j < num && found == 0; j++) {
            int min_x = 0, min_y = 0;
            findmin(dist, min_x, min_y);
            sptSet[min_x][min_y] = true;
            if (sptSet[dest_x][dest_y] == true) {
                found = 1;
                break;
            }
            //north
            if (grid[min_x - 1][min_y] == 1 && sptSet[min_x - 1][min_y] == false && dist[min_x - 1][min_y] > dist[min_x][min_y] + 1.0) {
                dist[min_x - 1][min_y] = dist[min_x][min_y] + 1.0;
                previous[min_x - 1][min_y] = make_pair(min_x, min_y);
            }
            //south
            if (grid[min_x + 1][min_y] == 1 && sptSet[min_x + 1][min_y] == false && dist[min_x + 1][min_y] > dist[min_x][min_y] + 1.0) {
                dist[min_x + 1][min_y] = dist[min_x][min_y] + 1.0;
                previous[min_x + 1][min_y] = make_pair(min_x, min_y);
            }
            //west
            if (grid[min_x][min_y - 1] == 1 && sptSet[min_x][min_y - 1] == false && dist[min_x][min_y - 1] > dist[min_x][min_y] + 1.0) {
                dist[min_x][min_y - 1] = dist[min_x][min_y] + 1.0;
                previous[min_x][min_y - 1] = make_pair(min_x, min_y);
            }
            //east:i,j+1
            if (grid[min_x][min_y + 1] == 1 && sptSet[min_x][min_y + 1] == false && dist[min_x][min_y + 1] > dist[min_x][min_y] + 1.0) {
                dist[min_x][min_y + 1] = dist[min_x][min_y] + 1.0;
                previous[min_x][min_y + 1] = make_pair(min_x, min_y);
            }
            //north-east:i-1,j+1
            if (grid[min_x - 1][min_y + 1] == 1 && sptSet[min_x - 1][min_y + 1] == false && dist[min_x - 1][min_y + 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x - 1][min_y] == 0 && grid[min_x][min_y + 1] == 0)) {
                dist[min_x - 1][min_y + 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x - 1][min_y + 1] = make_pair(min_x, min_y);
            }
            //south-east:i+1,j+1
            if (grid[min_x + 1][min_y + 1] == 1 && sptSet[min_x + 1][min_y + 1] == false && dist[min_x + 1][min_y + 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x + 1][min_y] == 0 && grid[min_x][min_y + 1] == 0)) {
                dist[min_x + 1][min_y + 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x + 1][min_y + 1] = make_pair(min_x, min_y);
            }
            //south-west:i+1,j-1
            if (grid[min_x + 1][min_y - 1] == 1 && sptSet[min_x + 1][min_y - 1] == false && dist[min_x + 1][min_y - 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x + 1][min_y] == 0 && grid[min_x][min_y - 1] == 0)) {
                dist[min_x + 1][min_y - 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x + 1][min_y - 1] = make_pair(min_x, min_y);
            }
            //north-west:i-1,j-1
            if (grid[min_x - 1][min_y - 1] == 1 && sptSet[min_x - 1][min_y - 1] == false && dist[min_x - 1][min_y - 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x - 1][min_y] == 0 && grid[min_x][min_y - 1] == 0)) {
                dist[min_x - 1][min_y - 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x - 1][min_y - 1] = make_pair(min_x, min_y);
            }
        }
    findpath(previous, dist, dest_x, dest_y, source_x, source_y);
}

int main() {
    int filled[num][num];       //to check whether cell is colored
    int grid[60][60];       //to map with obstacle
    for (int i = 0; i < 60; i++)
        for (int j = 0; j < 60; j++) {
            if (i == 0 || i == 59 || j == 0 || j == 59)        //borders
                grid[i][j] = 0;
            else
                grid[i][j] = 1;
        }
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++) {
            sptSet[i][j] = false;
            filled[i][j] = 0;
        }

    int source_x = 2, source_y = 2, dest_x = 58, dest_y = 58;
    Thread threadD(std::bind(&dijkstra, source_x, source_y, dest_x, dest_y, grid));
    RenderWindow window(VideoMode(1366, 768), "Grid");

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text1("  START", font, 15);
    sf::Text lengthD(" ", font, 24);

    RectangleShape buttonStartD(Vector2f(70, 25));       //button
    buttonStartD.setFillColor(Color::Green);
    CircleShape pathh(5);
    pathh.setFillColor(Color::White);
    RectangleShape yrectangle(Vector2f(10, 10));
    yrectangle.setFillColor(Color::Yellow);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int X = event.mouseButton.x;
                int Y = event.mouseButton.y;
                int row = Y / 10;       //row & column
                int col = X / 10;
                if (grid[row][col] == 0 && row < 60 && col < 60)
                    grid[row][col] = 1;
                else if (row < 60 && col < 60)
                    grid[row][col] = 0;
                cout << "Cell " << row << " , " << col << " state is: " << grid[row][col] << endl;
                if (X > 600 && X < 675 && Y>0 && Y < 25) {
                    threadD.launch();
                }
            }
        }
        window.clear();
        sf::Texture t;
        t.loadFromFile("bg.png");
        sf::Sprite s(t);
        s.scale(sf::Vector2f(.33f, .55f));
        window.draw(s);
        sf::Texture king;
        king.loadFromFile("king.png");
        sf::Sprite k(king);
        k.scale(sf::Vector2f(.035f, .035f));
        sf::Texture queen;
        queen.loadFromFile("queen.png");
        sf::Sprite q(queen);
        q.scale(sf::Vector2f(.035f, .035f));
        sf::Texture user;
        user.loadFromFile("user.png");
        sf::Sprite u(user);
        u.scale(sf::Vector2f(.06f, .06f));
        buttonStartD.setPosition(630, 0);
        window.draw(buttonStartD);
        text1.setPosition(630, 0);
        lengthD.setPosition(725, 0);
        window.draw(text1);
        stringstream ss1, ss2;
        ss1 << pathD.size();
        lengthD.setString(ss1.str());
        window.draw(lengthD);
        if (!pathD.empty()) {
            for (int i = 0; i < pathD.size(); i++) {
                pathh.setPosition(pathD[i].second * 10, pathD[i].first * 10);
                window.draw(pathh);
                filled[pathD[i].first][pathD[i].second] = 1;
            }
        }
        q.setPosition(source_y * 10, source_x * 10);
        window.draw(q);
        filled[source_x][source_y] = 1;
        k.setPosition(dest_y * 10, dest_x * 10);
        window.draw(k);
        filled[dest_x][dest_y] = 1;
        for (int i = 0; i <= 590; i += 10)
            for (int j = 0; j <= 590; j += 10) {
                if (grid[i / 10][j / 10] == 0) {
                    u.setPosition(j, i);
                    if (j > 0 && j < 590 && i>0 && i < 590) {
                        window.draw(u);
                    }
                }
                if (sptSet[i / 10][j / 10] == true && filled[i / 10][j / 10] == 0) {
                    yrectangle.setOutlineThickness(2);
                    yrectangle.setPosition(j, i);
                }
            }
        window.display();
    }
    return 0;
}
