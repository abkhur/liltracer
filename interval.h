#ifndef INTERVAL_H
#define INTERVAL_H

/*
manages real-valued intervals

author: abdullah khurram
written on: 10/3/2023
*/

class interval {
    public:
        double min, max;
        interval() : min(+infinity), max(-infinity) {} /*default set to empty*/
        interval(double _min, double _max) : min(_min), max(_max) {}

        bool contains(double x) const {
            return min <= x && x <= max;
        }

        bool surrounds(double x) const {
            return min < x && x < max;
        }

        double clamp(double x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        static const interval empty, universe;
};

const static interval empty (+infinity, -infinity);
const static interval universe (-infinity, +infinity);

#endif