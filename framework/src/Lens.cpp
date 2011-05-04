#include "Lens.h"
#include <limits>

Lens::Lens() {

	initializeLens();
	_apertureRadius = .40;

}

void Lens::initializeLens(string filename) {

	//half of lens farthest from film
	Sphere lens1(vec4(0,0,.2518,1), .5895, MaterialInfo(0,0,0,0,1,1.67),identity3D()); //lens surface nearest object space
	Sphere lens2(vec4(0,0,1.4341,1), 1.6966, MaterialInfo(0,0,0,0,1,1),identity3D());
	Sphere lens3(vec4(0,0,.1254,1), .3855, MaterialInfo(0,0,0,0,1,1.67),identity3D());
	Sphere lens4(vec4(0,0,.6358,1), .8154, MaterialInfo(0,0,0,0,1,1.699),identity3D());
	Sphere lens5(vec4(0,0,.1409,1), .255, MaterialInfo(0,0,0,0,1,1),identity3D());

	//half of lens nearest to film
	Sphere lens6(vec4(0,0,-.1999,1), .2899, MaterialInfo(0,0,0,0,1,1.603),identity3D());
	Sphere lens7(vec4(0,0,.929,1), .8154, MaterialInfo(0,0,0,0,1,1.658),identity3D());
	Sphere lens8(vec4(0,0,-.1728,1), .4077, MaterialInfo(0,0,0,0,1,1),identity3D());
	Sphere lens9(vec4(0,0,8.98,1), 8.74130, MaterialInfo(0,0,0,0,1,1.717),identity3D());
	Sphere lens10(vec4(0,0,-.4915,1), .7946, MaterialInfo(0,0,0,0,1,1),identity3D()); //lens surface farthest object space

	_lens.push_back(lens10); //push in reverse order to get order right
	_lens.push_back(lens9);
	_lens.push_back(lens8);
	_lens.push_back(lens7);
	_lens.push_back(lens6);
	_lens.push_back(lens5);
	_lens.push_back(lens4);
	_lens.push_back(lens3);
	_lens.push_back(lens2);
	_lens.push_back(lens1);

}

bool Lens::traceFirstHalf(Ray & r, Ray & exitRay, vec2 & offset) {

	vector<Sphere>::iterator lens = _lens.begin();
	Ray traceray = r;
	double oldIndex = 1.0;

	for(int i=0; i<5; i++) {
		
		double intersect = lens->intersect(traceray);
		if(intersect < numeric_limits<double>::infinity()) {
			vec4 pos = traceray.getPos(intersect);
			vec3 normal = vec3(lens->calculateNormal(pos), VW);
			double newIndex = lens->getRefractiveIndex();
			if(refractRay(traceray, normal, oldIndex, newIndex, pos)) {
				lens++;	
			}

			else
				return false;
		}
		else
			return false;
	}
	
	double currentZPos = traceray.getPos(0)[VZ];
	double t = traceray.getPos(0)[VZ] / traceray.direction()[VZ];

	vec4 exitRayPosition(traceray.getPos(t));

	exitRay = Ray(exitRayPosition, traceray.direction(), 0);
	return true;
}

bool refractRay(Ray & r, vec3 normal, double n1, double n2, vec4 pos) {

	normal.normalize();
	vec3 ray = -1 * vec3(r.direction(), VW);
	ray.normalize();

	double sin1 = 1 - (ray*normal);

	double sin2 = sin1*n1/n2;

	if(sin2 > 1 || sin2 < -1)
		return false;

	else {
		double cos1 = ray*normal;
		double cos2 = sqrt(1-(pow(n1/n2,2)*(1-pow(cos1,2))));
		vec4 newDir;
		if(ray * normal > 0)
			newDir = (n1/n2)*-1*ray + ((n1/n2)*cos1 - cos2)*normal;
		else
			newDir = (n1/n2)*-1*ray + ((n1/n2)*cos1 + cos2)*normal;

		r = Ray(pos,newDir,0);

		return true;
	}

}

Ray Lens::raytrace(Ray & r) {

	return Ray();
}

