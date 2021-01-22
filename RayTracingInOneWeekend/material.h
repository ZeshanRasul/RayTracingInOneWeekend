#pragma once

#include "rtweekend.h"
#include "hittable.h"

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const colour& a)
		:
		albedo(a)
	{}

	virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const override
	{
		auto scatter_direction = rec.normal + random_unit_vector();

		if (scatter_direction.near_zero())
		{
			scatter_direction = rec.normal;
		}

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	};

public:
	colour albedo;
};

class metal : public material
{
public:
	metal(const colour& a)
		:
		albedo(a)
	{}

	virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(r_in.getDirection(), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.getDirection(), rec.normal) > 0);
	}

public:
	colour albedo;
};


