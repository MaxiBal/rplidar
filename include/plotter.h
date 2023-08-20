#ifndef RPLDIAR_PLOTTER_H
#define RPLDIAR_PLOTTER_H

#include <sciplot/sciplot.hpp>

#include <valarray>

namespace rplidar
{

class plotter
{
    sciplot::Plot2D plot;

public:
    plotter();
    void plot_data(std::valarray<float> theta, std::valarray<float> r);
    void show();
};

};

#endif /* End of include guard: RPLIDAR_PLOTTER_H */