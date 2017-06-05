
#include "uncertainty_models.h"


uncertainty_model::uncertainty_model(model_type new_model_type)
{
	the_model_type = new_model_type;
}

uncertainty_model::uncertainty_model(uncertainty_model& existing_model)
{
	the_model_type = existing_model.the_model_type;
}

uncertainty_model& uncertainty_model::operator=(uncertainty_model& existing_model)
{
	the_model_type = existing_model.the_model_type;
	return *this;
}

uncertainty_model* uncertainty_model::copy()
{
	return new uncertainty_model(*this);
}

model_type uncertainty_model::get_model_type()
{
	return the_model_type;
}


crisp_value::crisp_value(uint16 new_val) : uncertainty_model(MT_CRISP)
{
	the_val = new_val;
}

crisp_value::crisp_value(crisp_value& existing_model) : uncertainty_model(existing_model.the_model_type)
{
	the_val = existing_model.the_val;
}

crisp_value& crisp_value::operator=(crisp_value& existing_model)
{
	uncertainty_model::operator=(existing_model);
	the_val = existing_model.the_val;
	return *this;
}

crisp_value* crisp_value::copy()
{
	return new crisp_value(*this);
}

uint16 crisp_value::get_val()
{
	return the_val;
}


epsilon::epsilon() : uncertainty_model(MT_EPSILON)
{
}

epsilon::epsilon(epsilon& existing_model) : uncertainty_model(the_model_type)
{
}

epsilon& epsilon::operator=(epsilon& existing_model)
{
	uncertainty_model::operator=(existing_model);
	return *this;
}

epsilon* epsilon::copy()
{
	return new epsilon(*this);
}


void probability_distribution::normalize()
{
	double total_sum = 0.0;
	for (uint16 i = 0; i < domain_size; i++)
	{
		total_sum += Pr[i];
	}
	for (uint16 i = 0; i < domain_size; i++)
	{
		Pr[i] /= total_sum;
	}
}

probability_distribution::probability_distribution(uint16 new_domain_size, double* new_Pr) : uncertainty_model(MT_PROBABILITY)
{
	domain_size = new_domain_size;
	Pr = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		Pr[i] = new_Pr[i];
	}
	normalize();
}

probability_distribution::probability_distribution(probability_distribution& existing_model) : uncertainty_model(existing_model)
{
	domain_size = existing_model.domain_size;
	Pr = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		Pr[i] = existing_model.Pr[i];
	}
}

probability_distribution& probability_distribution::operator=(probability_distribution& existing_model)
{
	uncertainty_model::operator=(existing_model);
	delete[] Pr;
	domain_size = existing_model.domain_size;
	Pr = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		Pr[i] = existing_model.Pr[i];
	}
	return *this;
}

probability_distribution* probability_distribution::copy()
{
	return new probability_distribution(*this);
}

probability_distribution::~probability_distribution()
{
	delete[] Pr;
}

uint16 probability_distribution::get_domain_size()
{
	return domain_size;
}

double probability_distribution::get_Pr(uint16 val)
{
	return Pr[val];
}

void probability_distribution::set_Pr(uint16 val, double new_Pr)
{
	Pr[val] = new_Pr;
	normalize();
}

void probability_distribution::set_Pr(double* new_Pr)
{
	for (uint16 i = 0; i < domain_size; i++)
	{
		Pr[i] = new_Pr[i];
	}
	normalize();
}


credal_set::credal_set(credal_set_type new_credal_set_type) : uncertainty_model(MT_CREDAL)
{
	the_credal_set_type = new_credal_set_type;
}

credal_set::credal_set(credal_set& existing_model) : uncertainty_model(existing_model)
{
	the_credal_set_type = existing_model.the_credal_set_type;
}

credal_set& credal_set::operator=(credal_set& existing_model)
{
	uncertainty_model::operator=(existing_model);
	the_credal_set_type = existing_model.the_credal_set_type;
	return *this;
}

credal_set* credal_set::copy()
{
	return new credal_set(*this);
}

credal_set::~credal_set()
{
}

credal_set_type credal_set::get_credal_set_type()
{
	return the_credal_set_type;
}


void extreme_points::normalize()
{
	for (uint16 j = 0; j < num_of_extreme_points; j++)
	{
		double total_sum = 0.0;
		for (uint16 i = 0; i < domain_size; i++)
		{
			total_sum += PrC[j][i];
		}
		for (uint16 i = 0; i < domain_size; i++)
		{
			PrC[j][i] /= total_sum;
		}
	}
}

extreme_points::extreme_points(uint16 new_domain_size, uint16 new_num_of_extreme_points, double** new_PrC) : credal_set(CST_LIST)
{
	domain_size = new_domain_size;
	num_of_extreme_points = new_num_of_extreme_points;
	PrC = new double*[num_of_extreme_points];
	for (uint16 j = 0; j < num_of_extreme_points; j++)
	{
		PrC[j] = new double[domain_size];
		for (uint16 i = 0; i < domain_size; i++)
		{
			PrC[j][i] = new_PrC[j][i];
		}
	}
	normalize();
}

extreme_points::extreme_points(extreme_points& existing_model) : credal_set(existing_model)
{
	domain_size = existing_model.domain_size;
	num_of_extreme_points = existing_model.num_of_extreme_points;
	PrC = new double*[num_of_extreme_points];
	for (uint16 j = 0; j < num_of_extreme_points; j++)
	{
		PrC[j] = new double[domain_size];
		for (uint16 i = 0; i < domain_size; i++)
		{
			PrC[j][i] = existing_model.PrC[j][i];
		}
	}
}

extreme_points& extreme_points::operator=(extreme_points& existing_model)
{
	credal_set::operator=(existing_model);
	for (uint16 j = 0; j < num_of_extreme_points; j++)
	{
		delete[] PrC[j];
	}
	delete[] PrC;
	domain_size = existing_model.domain_size;
	num_of_extreme_points = existing_model.num_of_extreme_points;
	PrC = new double*[num_of_extreme_points];
	for (uint16 j = 0; j < num_of_extreme_points; j++)
	{
		PrC[j] = new double[domain_size];
		for (uint16 i = 0; i < domain_size; i++)
		{
			PrC[j][i] = existing_model.PrC[j][i];
		}
	}
	return *this;
}

extreme_points* extreme_points::copy()
{
	return new extreme_points(*this);
}

extreme_points::~extreme_points()
{
	for (uint16 j = 0; j < num_of_extreme_points; j++)
	{
		delete[] PrC[j];
	}
	delete[] PrC;
}

uint16 extreme_points::get_domain_size()
{
	return domain_size;
}

double extreme_points::get_PrC(uint16 extreme_point, uint16 val)
{
	return PrC[extreme_point][val];
}


void interval_distribution::normalize()
{
	double PrL_sum = 0.0;
	double PrU_sum = 0.0;
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrL_sum += PrL[i];
		PrU_sum += PrU[i];
	}
	for (uint16 i = 0; i < domain_size; i++)
	{
		double new_PrL, new_PrU;
		new_PrL = MAX(PrL[i],1-(PrU_sum-PrU[i]));
		new_PrU = MIN(PrU[i],1-(PrL_sum-PrL[i]));
		PrL[i] = new_PrL;
		PrU[i] = new_PrU;
	}
}

interval_distribution::interval_distribution(uint16 new_domain_size, double* new_PrL, double* new_PrU) : credal_set(CST_INTERVAL)
{
	domain_size = new_domain_size;
	PrL = new double[domain_size];
	PrU = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrL[i] = new_PrL[i];
		PrU[i] = new_PrU[i];
	}
	normalize();
}

interval_distribution::interval_distribution(interval_distribution& existing_model) : credal_set(existing_model)
{
	domain_size = existing_model.domain_size;
	PrL = new double[domain_size];
	PrU = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrL[i] = existing_model.PrL[i];
		PrU[i] = existing_model.PrU[i];
	}
}

interval_distribution& interval_distribution::operator=(interval_distribution& existing_model)
{
	credal_set::operator=(existing_model);
	delete[] PrL;
	delete[] PrU;
	domain_size = existing_model.domain_size;
	PrL = new double[domain_size];
	PrU = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrL[i] = existing_model.PrL[i];
		PrU[i] = existing_model.PrU[i];
	}
	return *this;
}

interval_distribution* interval_distribution::copy()
{
	return new interval_distribution(*this);
}

interval_distribution::~interval_distribution()
{
	delete[] PrL;
	delete[] PrU;
}

uint16 interval_distribution::get_domain_size()
{
	return domain_size;
}

double interval_distribution::get_PrL(uint16 val)
{
	return PrL[val];
}

double interval_distribution::get_PrU(uint16 val)
{
	return PrU[val];
}


void Dempster_Shafer_model::normalize()
{
	double total_sum = 0.0;
	for (uint32 i = 0; i < num_of_sets; i++)
	{
		total_sum += m[i];
	}
	for (uint32 i = 0; i < num_of_sets; i++)
	{
		m[i] /= total_sum;
	}
}

Dempster_Shafer_model::Dempster_Shafer_model(uint16 new_domain_size, double* new_m) : credal_set(CST_DS)
{
	domain_size = new_domain_size;
	num_of_sets = 1 << domain_size;
	for (uint32 i = 0; i < num_of_sets; i++)
	{
		m[i] = new_m[i];
	}
	normalize();
}

Dempster_Shafer_model::Dempster_Shafer_model(Dempster_Shafer_model& existing_model) : credal_set(existing_model)
{
	domain_size = existing_model.domain_size;
	num_of_sets = 1 << domain_size;
	for (uint32 i = 0; i < num_of_sets; i++)
	{
		m[i] = existing_model.m[i];
	}
}

Dempster_Shafer_model& Dempster_Shafer_model::operator=(Dempster_Shafer_model& existing_model)
{
	credal_set::operator=(existing_model);
	delete[] m;
	domain_size = existing_model.domain_size;
	num_of_sets = 1 << domain_size;
	for (uint32 i = 0; i < num_of_sets; i++)
	{
		m[i] = existing_model.m[i];
	}
	return *this;
}

Dempster_Shafer_model* Dempster_Shafer_model::copy()
{
	return new Dempster_Shafer_model(*this);
}

Dempster_Shafer_model::~Dempster_Shafer_model()
{
	delete[] m;
}

uint16 Dempster_Shafer_model::get_domain_size()
{
	return domain_size;
}

double Dempster_Shafer_model::get_m(uint32 set)
{
	return m[set];
}


fuzzy_model::fuzzy_model(fuzzy_model_type new_fuzzy_model_type) : uncertainty_model(MT_FUZZY)
{
	the_fuzzy_model_type = new_fuzzy_model_type;
}

fuzzy_model::fuzzy_model(fuzzy_model& existing_model) : uncertainty_model(existing_model)
{
	the_fuzzy_model_type = existing_model.the_fuzzy_model_type;
}

fuzzy_model& fuzzy_model::operator=(fuzzy_model& existing_model)
{
	uncertainty_model::operator=(existing_model);
	the_fuzzy_model_type = existing_model.the_fuzzy_model_type;
	return *this;
}

fuzzy_model* fuzzy_model::copy()
{
	return new fuzzy_model(*this);
}

fuzzy_model::~fuzzy_model()
{
}

fuzzy_model_type fuzzy_model::get_fuzzy_model_type()
{
	return the_fuzzy_model_type;
}


void fuzzy_probability_distribution::normalize()
{
	double total_sum = 0.0;
	for (uint16 i = 0; i < domain_size; i++)
	{
		total_sum += c[i];
	}
	for (uint16 i = 0; i < domain_size; i++)
	{
		c[i] /= total_sum;
	}
}

fuzzy_probability_distribution::fuzzy_probability_distribution(uint16 new_domain_size, double* new_l, double* new_c, double* new_u) : fuzzy_model(FMT_PROBABILITY)
{
	domain_size = new_domain_size;
	l = new double[domain_size];
	c = new double[domain_size];
	u = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		l[i] = new_l[i];
		c[i] = new_c[i];
		u[i] = new_u[i];
	}
}

fuzzy_probability_distribution::fuzzy_probability_distribution(fuzzy_probability_distribution& existing_model) : fuzzy_model(existing_model)
{
	domain_size = existing_model.domain_size;
	l = new double[domain_size];
	c = new double[domain_size];
	u = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		l[i] = existing_model.l[i];
		c[i] = existing_model.c[i];
		u[i] = existing_model.u[i];
	}
}

fuzzy_probability_distribution& fuzzy_probability_distribution::operator=(fuzzy_probability_distribution& existing_model)
{
	fuzzy_model::operator=(existing_model);
	delete[] l;
	delete[] c;
	delete[] u;
	domain_size = existing_model.domain_size;
	l = new double[domain_size];
	c = new double[domain_size];
	u = new double[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		l[i] = existing_model.l[i];
		c[i] = existing_model.c[i];
		u[i] = existing_model.u[i];
	}
	return *this;
}
	
fuzzy_probability_distribution* fuzzy_probability_distribution::copy()
{
	return new fuzzy_probability_distribution(*this);
}

fuzzy_probability_distribution::~fuzzy_probability_distribution()
{
	delete[] l;
	delete[] c;
	delete[] u;
}

uint16 fuzzy_probability_distribution::get_domain_size()
{
	return domain_size;
}

double fuzzy_probability_distribution::get_l(uint16 val)
{
	return l[val];
}

double fuzzy_probability_distribution::get_c(uint16 val)
{
	return c[val];
}

double fuzzy_probability_distribution::get_u(uint16 val)
{
	return u[val];
}


semantic_distribution::semantic_distribution(uint16 new_domain_size, semantic_values* new_PrS) : fuzzy_model(FMT_SEMANTIC)
{
	domain_size = new_domain_size;
	PrS = new semantic_values[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrS[i] = new_PrS[i];
	}
}

semantic_distribution::semantic_distribution(semantic_distribution& existing_model) : fuzzy_model(existing_model)
{
	domain_size = existing_model.domain_size;
	PrS = new semantic_values[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrS[i] = existing_model.PrS[i];
	}
}

semantic_distribution& semantic_distribution::operator=(semantic_distribution& existing_model)
{
	uncertainty_model::operator=(existing_model);
	delete[] PrS;
	domain_size = existing_model.domain_size;
	PrS = new semantic_values[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrS[i] = existing_model.PrS[i];
	}
	return *this;
}

semantic_distribution* semantic_distribution::copy()
{
	return new semantic_distribution(*this);
}

semantic_distribution::~semantic_distribution()
{
	delete[] PrS;
}

uint16 semantic_distribution::get_domain_size()
{
	return domain_size;
}

semantic_values semantic_distribution::get_PrS(uint16 val)
{
	return PrS[val];
}


