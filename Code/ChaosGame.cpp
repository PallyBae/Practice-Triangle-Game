#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game

	RenderWindow window(vm, "Sierpinski Triangle!!", Style::Default);

    vector<Vector2f> vertices;   ///push_back stuff into us!
	vector<Vector2f> points;

    int poly_mid_x;
    int poly_mid_y;
    int false_poly_mid_x = 0;
    int false_poly_mid_y = 0;

	Vector2f clicked;

    //Adding the font we will use
    Font font;
    font.loadFromFile("KOMIKAP_.ttf");

    //Configuring the instruction text
    Text instruction_text;
    instruction_text.setFont(font);
    instruction_text.setString("LEFT CLICK to place vertices\nRIGHT CLICK to START");
    instruction_text.setCharacterSize(75);
    instruction_text.setFillColor(Color::White);

    //Configuring the point counter
    Text point_count_text;
    point_count_text.setFont(font);
    point_count_text.setString("Points = 0");
    point_count_text.setCharacterSize(100);
    point_count_text.setFillColor(Color::Green);

    //Positioning The Instruction Text
    FloatRect textRect = instruction_text.getLocalBounds();
    instruction_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    instruction_text.setPosition(1920/2.0f, 1080/2.0f);

    //Positioning The Point Counter
    point_count_text.setPosition(30, 30);


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
				if (event.mouseButton.button == sf::Mouse::Left && points.size() == 0)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 20)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    
                    clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;

				}
                else if (event.mouseButton.button == sf::Mouse::Right && vertices.size() >= 3)
                {
                    std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));

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
            const double PI = 3.141592653589793;
            int midpoint_x;
            int midpoint_y;
            int vert_select;
            double n = vertices.size();
            int sumtop = n/4;
            double cosine_k;
            double sum_total = 0;
            int largest_x = 0;
            int smallest_x = 0;
            int largest_y = 0;
            int smallest_y = 0;
            int translation_x = 0;
            int translation_y = 0;
            int poly_rad = 0;
            int false_largest_x = 0;
            int false_largest_y = 0;
            int false_smallest_x = 0;
            int false_smallest_y = 0;
            

            //Find the Midpoint of the Polygon
            for (int i = 0; i < vertices.size(); i ++)
            {
                //Find the top of the polygon
                if(vertices[i].y > largest_y)
                {
                    largest_y = vertices[i].y;
                }

                //Find the bottom of the polygon
                if(vertices[i].y < smallest_y)
                {
                    smallest_y = vertices[i].y;
                }

                //Calculate the midpoint y value
                poly_mid_y = (largest_y + smallest_y)/2;

                //Find the rightmost point of the Polygon
                if(vertices[i].x > largest_x)
                {
                    largest_x = vertices[i].x;
                }
                //Find the leftmost point of the Polygon
                if(vertices[i].x < smallest_x)
                {
                    smallest_x = vertices[i].x;
                }

                //Calculate the midpoint x value
                poly_mid_x = (largest_x + smallest_x)/2;
            }

            //Find the number of terms to add in the sum
            for(double k = 1; k < (sumtop + 1); k++)
            {
                cosine_k = cos((2*PI*k)/n);
                sum_total += cosine_k;
            }
            
            
            //summing the terms to calculate the scale factor r sub n
            double scale_factor = 1/( 2*(1 + sum_total));

            //Calculating the approximate radius of the polygon
            for (int i = 0; i < vertices.size(); i++)
            {
                //Adding fractions of the average radius length to create an approximate radius for the polygon
                poly_rad += (sqrt(pow((poly_mid_x - vertices[i].x),2) + pow((poly_mid_y - vertices[i].y),2)))/vertices.size();
            }

            //Calculating translations for the points
            for(int i = 0; i < vertices.size(); i++)
            {
                translation_x += (1-scale_factor)*poly_rad*(cos(2*PI*i)/vertices.size());
            }
            for(int i = 0; i < vertices.size(); i++)
            {
                translation_y += (1-scale_factor)*poly_rad*(sin(2*PI*i)/vertices.size());
            }
            
            //Calculating point positions based on randomly selected vertices
            for(int i = 0; i < 40000; i++)
            {
                srand(time(0) + i);
                //calculate the midpoint of the wrongly translated polygon
                if (points.size() > 200 && points.size() < 400)
                {
                    for (int i = 20; i < points.size(); i ++)
                    {
                        //Find the top of the polygon
                        if(points[i].y > false_largest_y)
                        {
                            false_largest_y = points[i].y;
                        }

                        //Find the bottom of the polygon
                        if(points[i].y < false_smallest_y)
                        {
                            false_smallest_y = points[i].y;
                        }

                        //Calculate the midpoint y value
                        false_poly_mid_y = (false_largest_y + false_smallest_y)/2;

                        //Find the rightmost point of the Polygon
                        if(points[i].x > false_largest_x)
                        {
                            false_largest_x = points[i].x;
                        }
                        //Find the leftmost point of the Polygon
                        if(points[i].x < false_smallest_x)
                        {
                            false_smallest_x = points[i].x;
                        }

                        //Calculate the midpoint x value
                        false_poly_mid_x = (false_largest_x + false_smallest_x)/2;
                        }
                }
                vert_select = (rand() % vertices.size());
                midpoint_x = (vertices[vert_select].x + points[points.size()-1].x)*scale_factor;
                midpoint_y = (vertices[vert_select].y + points[points.size()-1].y)*scale_factor;

                if(vertices.size() == 5)
                {
                    midpoint_x = -(vertices[vert_select].x - points[points.size()-1].x) / 8 * 3 + vertices[vert_select].x;
                    midpoint_y = -(vertices[vert_select].y - points[points.size()-1].y) / 8 * 3 + vertices[vert_select].y;
                }

                points.push_back(Vector2f(midpoint_x, midpoint_y));

                //Updating The Point Counting Text
                stringstream ss;
                ss << "Points = " << points.size();
                point_count_text.setString(ss.str());
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

        //Drawing Point Counter
        window.draw(point_count_text);

        //Drawing Instruction Text
        if(vertices.size() == 0)
        {
            window.draw(instruction_text);
        }

        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(2,2));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
        if(vertices.size() > 5)
        {
            for(int i = 20; i < points.size(); i++)
            {
                RectangleShape rectp(Vector2f(2,2));
                rectp.setPosition(Vector2f(points[i].x + (poly_mid_x - false_poly_mid_x), points[i].y + (poly_mid_y - false_poly_mid_y)));
                rectp.setFillColor(Color::Blue);
                window.draw(rectp);
            }
        }
        else
        {
            for(int i = 20; i < points.size(); i++)
            {
                RectangleShape rectp(Vector2f(3,3));
                rectp.setPosition(Vector2f(points[i].x, points[i].y));
                rectp.setFillColor(Color::Blue);
                window.draw(rectp);
            }
        }
        
        
        window.display();
    }

    return 0;
}