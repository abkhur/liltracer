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
        int samples_per_pixel = 10; // amnt of random samples per pixel
        int max_depth = 10; //i don't want to fry my shitty lenovo please god

        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << ' ' << imageHeight << "\n255\n";

            //render for loop
            for (int i = 0; i < imageHeight; ++i) {
                std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
                for (int j = 0; j < image_width; ++j) {
                    color pixel_color(0,0,0);
                    for (int sample = 0; sample < samples_per_pixel; ++sample) {
                        ray r = get_ray(j, i);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_color, samples_per_pixel);
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

        ray get_ray(int i, int j) const {
            /*gets a random camera ray for pixel at (i,j)*/
            auto pixel_center = pixel00Location+(i*pixel_delta_u)+(j*pixel_delta_v);
            auto pixel_sample = pixel_center + pixel_sample_square();

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 pixel_sample_square() const {
            /*returns a random point in the square surrounding a pixel*/
            auto px = -0.5 + random_double();
            auto py = -0.5 + random_double();
            return (px*pixel_delta_u) + (py*pixel_delta_v);
        }

        color ray_color(const ray& r, int depth, const hittable& world) const {
            hit_record rec;

            if (depth <= 0) {
                return color(0,0,0);
            }

            if (world.hit(r, interval(0.001, infinity), rec)) {
                vec3 direction = random_on_hemisphere(rec.normal);
                return 0.5*ray_color(ray(rec.p,direction),depth-1,world);
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};
#endif