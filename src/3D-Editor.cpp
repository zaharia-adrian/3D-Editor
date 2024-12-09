#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../src/utils/Mat4x4.hpp"
#include "../src/utils/Vec3d.hpp"
#include "../src/feature/Scene.hpp"
#include <filesystem>



const float HEIGHT = 1980; /// window width
const float WIDTH = 1020; ///window height



int main()
{
    float theta = 0;
    std::cout << std::filesystem::current_path();

    sf::RenderWindow window(sf::VideoMode(800, 600), "3D-Editor");
 

    Scene S(800,600);
    S.loadFromFile("../../../localProjects/Spaceship.txt");
    
    
  
   
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape
                )
                window.close();
            /*if (event.type == sf::Event::MouseMoved)
                std::cout << "moves...\n";*/
            //m1.handleMoveCamera(event);
            S.handleMoveCamera(event);
 
        }
        
        window.clear(sf::Color::Black);

        S.draw(window);
        //m1.draw(window);
        window.display();
        /*
        std::vector<triangle> final;
        for (triangle tri : m.tris) {
            triangle triProj, triTranslated, triRotX,triRotZ;

            
            vec3d normal, line1, line2;

            line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
            line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
            line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

            line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
            line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
            line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

            normal.x = line1.y * line2.z - line1.z * line2.y;
            normal.y = line1.x * line2.z - line1.z * line2.x;
            normal.z = line1.x * line2.y - line1.y * line2.x;

            float l = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
            normal.x /= l; normal.y /= l; normal.z /= l;
            std::cout << l << '\n';

            //std::cout << normal.z << ' ';

            float dotProd = normal.x * (triTranslated.p[0].x - Camera.x) +
                normal.y * (triTranslated.p[0].y - Camera.y) +
                normal.z * (triTranslated.p[0].z - Camera.z);

            if (dotProd<0.0f) {

                for (int i = 0;i < 3;i++)
                    multiplyVectorMaxtrix(triTranslated.p[i], triProj.p[i], projection_matrix);

                triProj.p[0].x += 1.0f; triProj.p[0].y += 1.0f;
                triProj.p[1].x += 1.0f; triProj.p[1].y += 1.0f;
                triProj.p[2].x += 1.0f; triProj.p[2].y += 1.0f;
                triProj.p[0].x *= 0.5f * WIDTH;
                triProj.p[0].y *= 0.5f * HEIGHT;
                triProj.p[1].x *= 0.5f * WIDTH;
                triProj.p[1].y *= 0.5f * HEIGHT;
                triProj.p[2].x *= 0.5f * WIDTH;
                triProj.p[2].y *= 0.5f * HEIGHT;

                final.push_back(triProj);

                drawTriangle(triProj);
            }
            
            sort(final.begin(), final.end(), [](triangle &t1, triangle &t2) {
                float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
                float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
                return (z1 > z2);
                });
            for (triangle &tri : final) {
                drawTriangle(tri);
            }
        }
     */
    }
    return 0;
}

