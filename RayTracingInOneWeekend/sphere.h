#pragma once
#include "hittable.h"

class sphere : public hittable
{
public:
	sphere() {};
	sphere(point3 cen, double r)
		:
		center(cen),
		radius(r)
	{}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 center;
	double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.getOrigin() - center;
	auto a = r.getDirection().length_squared();
	auto half_b = dot(oc, r.getDirection());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;
	
	if (discriminant < 0)
	{
		return false;
	};

	auto sqrtd = sqrt(discriminant);

	auto root = (-half_b - sqrtd) / a;
	
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);

	return true;
}