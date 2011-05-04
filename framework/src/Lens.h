#ifndef LENS_H_
#define LENS_H_

#include "global.h"
#include "Primitives.h"
#include "BoundingBox.h"
#include "World.h"
#include "Viewport.h"

class Lens {
public:
	Lens();
	//Lens(string filename);
	~Lens();
	void initializeLens(string filename="sample");
	//void addLens(Sphere s1, Sphere s2);
	Ray raytrace(Ray & r);
	bool traceFirstHalf(Ray & r, Ray & exitRay, vec2 & offset);

private:
	vector<Sphere> _lens; //every 2 spheres represent the surfaces of each lens
	double _apertureRadius; //radius of aperture
	//vector<double> _thickness; //each element represents either the thickness of the lens or the space in between lens

}
#endif