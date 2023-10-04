#include "liltracer.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

/*
main class for liltracer

if you're reading this, why not say hi to me? 
my email's abkhur@vt.edu :)

created by:
abdullah khurram

10/3/2023
*/

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5* (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    /*image initialization*/
    auto aspectRatio = 16.0/9.0; //my laptop has a 16:9 aspect ratio so that's what you're getting
    int image_width = 400;

    /*calculating image height; we want it to be >= 1*/
    int imageHeight = static_cast<int>(image_width/aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    /*world setup*/
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100));

    /*camera setup*/
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (static_cast<double>(image_width)/imageHeight);
    auto cameraCenter = point3(0,0,0);

    /*Calculate the vectors across horizontal/vert viewport*/
    auto viewport_u = vec3(viewportWidth, 0, 0);
    auto viewport_v = vec3(0, -viewportHeight, 0);

    /*Calculates per-pixel delta vectors; horizontal and vertical*/
    auto pixel_delta_u = viewport_u/image_width;
    auto pixel_delta_v = viewport_v/imageHeight;

    /*Calculates position of top-leftmost pixel*/
    auto viewportUpperLeft = cameraCenter - vec3(0,0,focalLength) - viewport_u/2 - viewport_v/2;
    auto pixel00Location = viewportUpperLeft+0.5*(pixel_delta_u + pixel_delta_v);

    /*render*/

    std::cout << "P3\n" << image_width << ' ' << imageHeight << "\n255\n";

    //render for loop
    for (int i = 0; i < imageHeight; ++i) {
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; ++j) {
            auto pixelCenter = pixel00Location + (j * pixel_delta_u) + (i * pixel_delta_v);
            auto rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);

            color pixelColor = ray_color(r, world);
            write_color(std::cout, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
}