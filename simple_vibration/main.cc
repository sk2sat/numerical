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
const int interval	= 10;

inline vector<> func(vector<> x){
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
	vector<> k1,k2,k3,k4;
	double t = 0.;

	for(auto i = 0; t<t_limit; i++){
		if(i%interval == 0){
#ifdef USE_GNUPLOT
			gp.command("plot '-' w l linewidth 3");
			gp.command("0.0 0.0");
			// ホントはこれはやるべきではない(sksat::math::gnuplot::gpは本来private member)
			fprintf(gp.gp, "%f %f\n", x.get_x(), 0.0);
			gp.command("e");
#else
			std::cout << t
					<< " " << x.get_x()
				//	<< " " << x.get_y()
					<< std::endl;
#endif
		}

// Euler method
//		x = x + dt * func(x);

// RK4 method
		k1 = func(x);
		k2 = func(x + dt / 2. * k1);
		k3 = func(x + dt / 2. * k2);
		k4 = func(x + dt * k3);
		x = x + dt / 6. * (k1 + 2.0*k2 + 2.0*k3 +k4);

		t = i * dt;
	}
	return 0;
}
