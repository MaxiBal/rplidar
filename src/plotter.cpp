#include <plotter.h>


namespace rplidar
{

plotter::plotter() 
{
    plot.xlabel("X");
    plot.ylabel("Y");
}

void plotter::plot_data(std::valarray<float> theta, std::valarray<float> r)
{
    plot.drawPoints(std::cos(theta) * r, std::sin(theta) * r).pointType(0);
}

void plotter::show()
{
    // Create figure to hold plot
    sciplot::Figure fig = {{plot}};
    // Create canvas to hold figure
    sciplot::Canvas canvas = {{fig}};

    // Show the plot in a pop-up window
    canvas.show();
}

};