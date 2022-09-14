#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game

	RenderWindow window(vm, "Sierpinski Triangle!!", Style::Default);

    vector<Vector2f> vertices;   ///push_back stuff into us!
	vector<Vector2f> points;

	Vector2f clicked;

    while (window.isOpen())
	{
        Event event;
        while (window.pollEvent(event))
		{
            if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        ///fourthclick
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        ///maybe unnecessary
                    }
                    clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;

				}
			}
    
		}

        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}


        /*
        ****************************************
        Update the scene
        ****************************************
        */
        ///Vector2f v(2,2);
        ///RectangleShape rect(v);
        
        
        if(points.size() > 0)
        {
            int midpoint_x;
            int midpoint_y;
            int vert_select;

            for(int i = 0; i < 100; i++)
            {
                srand(time(0) + i);
                vert_select = (rand() % 3);
                midpoint_x = (vertices[vert_select].x + points[points.size()-1].x)/2;
                midpoint_y = (vertices[vert_select].y + points[points.size()-1].y)/2;
                points.push_back(Vector2f(midpoint_x, midpoint_y));
            }
            

            ///generate point
            ///select random vertex
            ///calculate midpoint between vertex and last point in vector
            ///pushback newly generated coordinate
        }
        
        /*
        ****************************************
        Draw the scene
        ****************************************
        */

        ///loop through vectors and draw each coordinate
        // Clear everything from the last run frame
        window.clear();
        // Draw our game scene here
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(1,1));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
        for(int i = 1; i < points.size(); i++)
        {
            RectangleShape rectp(Vector2f(1,1));
            rectp.setPosition(Vector2f(points[i].x, points[i].y));
            rectp.setFillColor(Color::Blue);
            window.draw(rectp);
        }
        
        window.display();
    }

    return 0;
}