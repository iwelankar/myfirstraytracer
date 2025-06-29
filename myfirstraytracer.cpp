// myfirstraytracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "rtweekend.h"
#include "camera.h"
/*#include "color.h"
#include "vec3.h"
#include "ray.h*/
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
//#include <iostream>


//double hit_sphere(const point3& center, double radius, const ray& r) {
//    vec3 oc = center - r.origin();
//    //b = -2h taken to make calculations easier.
//    auto a = r.direction().length_squared();
//    auto h = dot(r.direction(), oc);
//    auto c = oc.length_squared() - radius * radius;
//    auto discriminant = h * h - a * c;
//
//    if (discriminant < 0) {
//        return -1.0;
//    }
//    else {
//        return (h - std::sqrt(discriminant)) / a;
//    }
//}


//int main()
//{
//    hittable_list world;
//
//    /*world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
//    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));*/
//
//    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
//    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
//    auto material_left = make_shared<dielectric>(1.50);
//    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
//    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
//
//    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
//    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
//    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
//    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
//    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
//
//    camera cam;
//
//    cam.aspect_ratio = 16.0 / 9.0;
//    cam.image_width = 400;
//    cam.samples_per_pixel = 100;
//    cam.max_depth = 50;
//
//    cam.vfov = 20;
//    cam.lookfrom = point3(-2, 2, 1);
//    cam.lookat = point3(0, 0, -1);
//    cam.vup = vec3(0, 1, 0);
//
//    cam.defocus_angle = 10.0;
//    cam.focus_dist = 3.4;
//
//    cam.render(world);
//}
/*
int main() {
    hittable_list world;

    // Light grey ground instead of whitish
    auto ground_material = make_shared<lambertian>(color(0.7, 0.7, 0.7));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    // Generate random small spheres
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                // Vary sphere sizes
                auto sphere_radius = 0.15 + 0.1 * random_double(); // Random size between 0.15 and 0.25

                if (choose_mat < 0.8) {
                    // Diffuse - green and blue shades only
                    color albedo;
                    if (random_double() < 0.5) {
                        // Green shades
                        albedo = color(random_double(0.1, 0.4),   // Low red
                            random_double(0.3, 0.9),   // High green
                            random_double(0.1, 0.4));  // Low blue
                    }
                    else {
                        // Blue shades
                        albedo = color(random_double(0.1, 0.4),   // Low red
                            random_double(0.1, 0.5),   // Low green
                            random_double(0.4, 0.9));  // High blue
                    }
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, sphere_radius, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // Metal - green and blue metallic shades
                    color albedo;
                    if (random_double() < 0.5) {
                        // Metallic green
                        albedo = color(random_double(0.2, 0.5),
                            random_double(0.5, 1.0),
                            random_double(0.2, 0.5));
                    }
                    else {
                        // Metallic blue
                        albedo = color(random_double(0.2, 0.5),
                            random_double(0.2, 0.6),
                            random_double(0.5, 1.0));
                    }
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, sphere_radius, sphere_material));
                }
                else {
                    // Glass - keep as is
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, sphere_radius, sphere_material));
                }
            }
        }
    }

    // Three large spheres with varied sizes
    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.2, material1)); // Slightly larger glass

    // Large green diffuse sphere
    auto material2 = make_shared<lambertian>(color(0.2, 0.6, 0.3));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 0.8, material2)); // Smaller than original

    // Large blue metal sphere
    auto material3 = make_shared<metal>(color(0.3, 0.5, 0.8), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.1, material3)); // Slightly larger

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1920;
    cam.samples_per_pixel = 750;
    cam.max_depth = 50;
    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);
    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    cam.render(world);
}
*/
// SCENE: RAINBOW SPHERES IN A CIRCLE
int main() {
    hittable_list world;

    // Ground
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    // Rainbow colors in order
    std::vector<color> rainbow_colors = {
        color(1.0, 0.0, 0.0),   // Red
        color(1.0, 0.5, 0.0),   // Orange  
        color(1.0, 1.0, 0.0),   // Yellow
        color(0.0, 1.0, 0.0),   // Green
        color(0.0, 0.0, 1.0),   // Blue
        color(0.3, 0.0, 0.8),   // Indigo
        color(0.8, 0.0, 1.0)    // Violet
    };

    // Create circle of rainbow spheres
    double radius_of_circle = 4.0;
    for (int i = 0; i < 7; i++) {
        double angle = i * 2 * pi / 7;  // Divide circle into 7 parts
        double x = radius_of_circle * cos(angle);
        double z = radius_of_circle * sin(angle);

        auto rainbow_material = make_shared<lambertian>(rainbow_colors[i]);
        world.add(make_shared<sphere>(point3(x, 0.8, z), 0.8, rainbow_material));
    }

    // Optional: Add a white sphere in the center
    auto center_material = make_shared<lambertian>(color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0, 0.5, 0), 0.5, center_material));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 150;
    cam.max_depth = 20;
    cam.vfov = 35;
    cam.lookfrom = point3(8, 6, 8);
    cam.lookat = point3(0, 0.8, 0);
    cam.vup = vec3(0, 1, 0);
    cam.defocus_angle = 0.0;
    cam.focus_dist = 12.0;

    cam.render(world);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
