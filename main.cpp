#include <bits/stdc++.h>
using namespace std;

/*
input:
list of (location, size, list of (percentage, destination)
output:
lowest cost
highest cost
*/

constexpr float TOTAL_BUDGET = 10000000.f;

enum Type {
	Small, Medium, Large
};

enum class Region {
	Asgard, Ragnarok, Jotunn, Valhalla
};

enum class Location {
	Trondheim = 0, Viborg, Ribe, Hedeby, Helsingborg, Roskilde, Visby, Paaviken, Skara, Sarpsborg
};

struct Distrib {
	float percentage;
	Region dest;
};

struct Factory
{
	Location loc;
	Type type;
	vector<Distrib> distrib;
};

struct Result {
	float highest, lowest;
};

float fixed_costs(Location loc) {
	switch (loc) {
	case Location::Trondheim:
		return 118.f;
	case Location::Viborg:
		return 119.f;
	case Location::Ribe:
		return 114.f;
	case Location::Hedeby:
		return 117.f;
	case Location::Helsingborg:
		return 115.f ;
	case Location::Roskilde:
		return 104.f;
	case Location::Visby:
		return 102.f;
	case Location::Paaviken:
		return 108.f;
	case Location::Skara:
		return 112.f;
	case Location::Sarpsborg:
		return 110.f;
	default:
		assert(0);
	}
};

float variable_costs(Location loc) {
	switch (loc) {
	case Location::Trondheim:
		return 0.42;
	case Location::Viborg:
		return 0.37;
	case Location::Ribe:
		return 0.63;
	case Location::Hedeby:
		return 0.48;
	case Location::Helsingborg:
		return 0.60;
	case Location::Roskilde:
		return 1.14;
	case Location::Visby:
		return 1.25;
	case Location::Paaviken:
		return 0.95;
	case Location::Skara:
		return 0.73;
	case Location::Sarpsborg:
		return 0.85;
	default:
		assert(0);
	}
};

float sourcing_costs(Location loc) {
	switch (loc) {
	case Location::Trondheim:
		return 1382000.f;
	case Location::Viborg:
		return 1382000.f;
	case Location::Ribe:
		return 1304000.f;
	case Location::Hedeby:
		return 1430000.f;
	case Location::Helsingborg:
		return 1400000.f;
	case Location::Roskilde:
		return 1264000.f;
	case Location::Visby:
		return 1328000.f;
	case Location::Paaviken:
		return 1442000.f;
	case Location::Skara:
		return 1442000.f;
	case Location::Sarpsborg:
		return 1378000.f;
	default:
		assert(0);
	}
};

float area(Type type)
{
	switch (type) {
	case Type::Small:
		return 6800.f;
	case Type::Medium:
		return 10500.f;
	case Type::Large:
		return 14000.f;
	default:
		assert(0);
	}
}

float production_cap(Type type)
{
	switch (type) {
	case Type::Small:
		return 130000.f;
	case Type::Medium:
		return 195000.f;
	case Type::Large:
		return 260000.f;
	default:
		assert(0);
	}
}

float transport_cost(float units, int distance)
{
	if (units >= 0.f && units <= 35000.f)
		return (float)(distance * 1900);
	else if (units <= 60000.f)
		return (float)(distance * 2100);
	else if (units <= 100000.f)
		return (float)(distance * 2300);
	else
		return (float)(distance * 2500);
}

float distance(Location loc, Region dest)
{
	switch(dest) {
	case Region::Asgard:
		switch (loc) {
		case Location::Trondheim:
			return 114.f;
		case Location::Viborg:
			return 123.f;
		case Location::Ribe:
			return 189.f;
		case Location::Hedeby:
			return 198.f;
		case Location::Helsingborg:
			return 204.f;
		case Location::Roskilde:
			return 175.f;
		case Location::Visby:
			return 188.f;
		case Location::Paaviken:
			return 202.f;
		case Location::Skara:
			return 192.f;
		case Location::Sarpsborg:
			return 185.f;
		default:
			assert(0);
		}
	case Region::Ragnarok:
		switch (loc) {
		case Location::Trondheim:
			return 190.f;
		case Location::Viborg:
			return 180.f;
		case Location::Ribe:
			return 108.f;
		case Location::Hedeby:
			return 118.f;
		case Location::Helsingborg:
			return 126.f;
		case Location::Roskilde:
			return 180.f;
		case Location::Visby:
			return 176.f;
		case Location::Paaviken:
			return 198.f;
		case Location::Skara:
			return 200.f;
		case Location::Sarpsborg:
			return 196.f;
		default:
			assert(0);
		}
	case Region::Jotunn:
		switch (loc) {
		case Location::Trondheim:
			return 208.f;
		case Location::Viborg:
			return 188.f;
		case Location::Ribe:
			return 175.f;
		case Location::Hedeby:
			return 194.f;
		case Location::Helsingborg:
			return 190.f;
		case Location::Roskilde:
			return 105.f;
		case Location::Visby:
			return 110.f;
		case Location::Paaviken:
			return 187.f;
		case Location::Skara:
			return 199.f;
		case Location::Sarpsborg:
			return 188.f;
		default:
			assert(0);
		}
	case Region::Valhalla:
		switch (loc) {
		case Location::Trondheim:
			return 179.f;
		case Location::Viborg:
			return 200.f;
		case Location::Ribe:
			return 180.f;
		case Location::Hedeby:
			return 205.f;
		case Location::Helsingborg:
			return 180.f;
		case Location::Roskilde:
			return 172.f;
		case Location::Visby:
			return 190.f;
		case Location::Paaviken:
			return 134.f;
		case Location::Skara:
			return 130.f;
		case Location::Sarpsborg:
			return 120.f;
		default:
			assert(0);
		}
	default:
		assert(0);
	}
}

float importance_factor(Region region)
{
	//0.95 - 1.15
	switch(region) {
	case Region::Asgard:
		return 0.95;
	case Region::Ragnarok:
		return 1.15;
	case Region::Jotunn:
		return 1.0;
	case Region::Valhalla:
		return 0.95;
	default:
		assert(0);
	}
}

Result simulate(vector<Factory> factories)
{
	float total_cost, remaining;

	total_cost = 0.f;
	//sourcing + production cost
	for(const auto& factory: factories) {
		total_cost += fixed_costs(factory.loc) * area(factory.type) +
			variable_costs(factory.loc) * production_cap(factory.type)
			+ sourcing_costs(factory.loc);
		if (total_cost > TOTAL_BUDGET) {
			cerr << "ERROR: Costs exceeded at sourcing and production: " << total_cost << '\n';
			exit(1);
		}
	}

	unordered_map<Region, float> region_units; // units to each region
	//distribution costs
	for(const auto& f: factories) {
		for(const auto& x: f.distrib) {
			float units = x.percentage/100*production_cap(f.type);
			float d = distance(f.loc, x.dest);
			total_cost += transport_cost(units, d);

			region_units[x.dest] += units;

			if (total_cost > TOTAL_BUDGET) {
				cerr << "ERROR: Costs exceeded at distribution: " << total_cost << '\n';
				exit(1);
			}
		}
	}

	remaining = TOTAL_BUDGET - total_cost;

	Result result = {remaining, remaining};
	for(const auto& [dest, units]: region_units) {
		result.lowest += importance_factor(dest) * units * 20.0;
		result.highest += importance_factor(dest) * units * 35.0;
	}
	return result;
}

int main()
{
	/*
	  Results:
	  Lowest possible: 1.0777e+07
	  Average possible: 1.28732e+07
	  Highest possible: 1.49695e+07
	*/
	// vector<Factory> factories = {
	// 	{Location::Ribe, Type::Small, {{100.f, Region::Ragnarok}}},
	// 	{Location::Roskilde, Type::Small, {{100.f, Region::Jotunn}}},
	// };
	
	vector<Factory> factories = {
		{Location::Ribe, Type::Large, {{100.f, Region::Ragnarok}}},
		{Location::Roskilde, Type::Large, {{100.f, Region::Jotunn}}},
		{Location::Trondheim, Type::Medium, {
				{51.f, Region::Asgard},
				{49.f, Region::Valhalla},
			}},
	};

	auto [highest, lowest] = simulate(factories);
	cout <<"Results:\n"
		 << "Lowest possible: " << lowest << '\n'
		 << "Average possible: " << (highest+lowest)/2.f << '\n'
		 << "Highest possible: " << highest << '\n';

	return 0;
}
