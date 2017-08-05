#include <iostream>
#include <sksat/math/vector.hpp>
#include <sksat/math/gnuplot.hpp>

#define USE_GNUPLOT

using sksat::math::vector;
using sksat::math::gnuplot;

const double k 		= 1.;
const double m		= 1.;
const double x_init	= 1.;
const double v_init	= 0.;
const double dt		= 0.001;
const double t_limit= 20.;

inline vector<> func(vector<>& x){
	return vector<>{
		x.get_y(),
		- k / m * x.get_x(),
	};
}

int main(int argc, char **argv){
#ifdef USE_GNUPLOT
	gnuplot gp(gnuplot::PERSIST);
	gp.command("set xr [-1.1:1.1]");
	gp.command("set yr [-0.1:0.1]");
	gp.command("set grid");
#endif
	vector<> x(x_init, v_init);
	double t = 0.;

	for(auto i = 0; t<t_limit; i++){
#ifdef USE_GNUPLOT
		gp.command("plot '-' w l linewidth 3");
		gp.command("0.0 0.0");
		fprintf(gp.gp, "%f %f\n", x.get_x(), 0.0);
		gp.command("e");
#else
		std::cout << t
				<< " " << x.get_x()
			//	<< " " << x.get_y()
				<< std::endl;
#endif
		x = x + dt * func(x);
		t = i * dt;
	}
	return 0;
}
