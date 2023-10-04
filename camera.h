#ifndef CAMERA_H
#define CAMERA_H

#include "liltracer.h"

#include "color.h"
#include "hittable.h"

#include <iostream>

/*
consolidating camera and render code here
makes it easier for me yfm? --abkhur

written by: abdullah khurram
on: 10/3/2023
*/

class camera {
    public:
        /*image initialization*/
        double aspectRatio = 1.0; //my laptop has a 16:9 aspect ratio so that's what you're getting
        int image_width = 100;
        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << ' ' << imageHeight << "\n255\n";

            //render for loop
            for (int i = 0; i < imageHeight; ++i) {
                std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
                for (int j = 0; j < image_width; ++j) {
                    auto pixelCenter = pixel00Location + (j * pixel_delta_u) + (i * pixel_delta_v);
                    auto rayDirection = pixelCenter - center;
                    ray r(center, rayDirection);

                    color pixelColor = ray_color(r, world);
                    write_color(std::cout, pixelColor);
                }
            }
            std::clog << "\rDone.                 \n";
        }
    
    private:
        /*todo*/
        int imageHeight; // rendered image height in pixels
        point3 center; //center of camera
        point3 pixel00Location; //the location of px(0,0)
        vec3 pixel_delta_u; //offset pixel horizontal towards right
        vec3 pixel_delta_v; //offset pixel vertical towards the bottom

        void initialize() {
            imageHeight = static_cast<int>(image_width/aspectRatio);
            imageHeight = (imageHeight < 1) ? 1 : imageHeight;

            center = point3(0,0,0);

            /*finding viewport dimensions*/
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (static_cast<double>(image_width)/imageHeight);

            /*Calculating vectors on the horizontal and vertical*/
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            /*Calculate horizontal/vertical delta vectors per-pixel*/
            pixel_delta_u = viewport_u/image_width;
            pixel_delta_v = viewport_v/imageHeight;

            /*Calculate the position of px(0,0)*/
            auto viewport_upper_left = center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
            pixel00Location = viewport_upper_left + 0.5 * (pixel_delta_u+pixel_delta_v);
        }

        color ray_color(const ray& r, const hittable& world) {
            hit_record rec;
            if (world.hit(r, interval(0, infinity), rec)) {
                return 0.5* (rec.normal + color(1,1,1));
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};
#endif