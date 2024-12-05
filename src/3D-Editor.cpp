#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../src/utils/Mat4x4.hpp"
#include "../src/utils/Vec3d.hpp"

const float HEIGHT = 600.0f; /// window width
const float WIDTH = 800.0f; ///window height
const float a = HEIGHT / WIDTH; ///aspect ratio
const float PI = 4 * atan(1.); /// PI 3.14...
const float theta = PI / 2; /// view angle 
const float zfar = 1000.0f; ///distance to far plan
const float znear = 0.1f; /// distante to near plan
const float fov = 1.0f/tan(theta / 2); /// field of view
const float q = zfar / (zfar - znear);


int main()
{
    float theta = 0;
    sf::Clock clock;
    vec3d Camera = { 0.0f,0.0f,0.0f };

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "3D-Editor");


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }
        mesh m; 
        m.tris = {

            // SOUTH
            { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

            // EAST                                                      
            { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

            // NORTH                                                     
            { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

            // WEST                                                      
            { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

            //TOP                                                       
           { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
           { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

           //BOTTOM                                                    
          { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
          { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

        };

        mat4x4 projection_matrix = {
            a * fov, 0, 0, 0,
            0, fov, 0, 0,
            0, 0, q, 1,
            0, 0, -znear * q, 0
        };
        theta += clock.getElapsedTime().asSeconds()/10.0f;
        mat4x4 rotation_matrix_x = {
             1,0,0,0,
             0,cosf(theta * 0.5f),sinf(theta * 0.5f),0,
             0,-sinf(theta * 0.5f),cosf(theta * 0.5f),0,
             0,0,0,1
        };
        mat4x4 rotation_matrix_z = {
             cosf(theta),sinf(theta),0,0,
             -sinf(theta),cosf(theta),0,
             0,0,1,0,
             0,0,0,1
        };


        window.clear(sf::Color::Black);
        std::vector<triangle> final;
        for (triangle tri : m.tris) {
            triangle triProj, triTranslated, triRotX,triRotZ;

            triRotX = tri;
            for (int i = 0;i < 3;i++)
                multiplyVectorMaxtrix(tri.p[i], triRotX.p[i], rotation_matrix_x);

            triRotZ = triRotX;
            for (int i = 0;i < 3;i++)
                multiplyVectorMaxtrix(triRotX.p[i], triRotZ.p[i], rotation_matrix_z);

            triTranslated = triRotZ;
            for(int i=0;i<3;i++)
                triTranslated.p[i].z += 3.0f;   
            
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
            auto drawLine = [&](Vec3d v1, Vec3d v2) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(v1.x,v1.y)),
                    sf::Vertex(sf::Vector2f(v2.x,v2.y))

                };
                std::cout << v1.x << ' ' << v1.y << " | " << v2.x << ' ' << v2.y << '\n';
                window.draw(line, 2, sf::Lines);
                };
            auto drawTriangle = [&](triangle& tri) {
                drawLine(tri.p[0], tri.p[1]);
                drawLine(tri.p[0], tri.p[2]);
                drawLine(tri.p[1], tri.p[2]);
                };
            sort(final.begin(), final.end(), [](triangle &t1, triangle &t2) {
                float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
                float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
                return (z1 > z2);
                });
            for (triangle &tri : final) {
                drawTriangle(tri);
            }
        }



        window.display();
    }

    return 0;

}

