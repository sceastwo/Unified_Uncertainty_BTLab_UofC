
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


void credal_set::normalize()
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

credal_set::credal_set(uint16 new_domain_size, uint16 new_num_of_extreme_points, double** new_PrC) : uncertainty_model(MT_CREDAL)
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

credal_set::credal_set(credal_set& existing_model) : uncertainty_model(existing_model)
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

credal_set& credal_set::operator=(credal_set& existing_model)
{
	uncertainty_model::operator=(existing_model);
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

credal_set* credal_set::copy()
{
	return new credal_set(*this);
}

credal_set::~credal_set()
{
	for (uint16 j = 0; j < num_of_extreme_points; j++)
	{
		delete[] PrC[j];
	}
	delete[] PrC;
}

uint16 credal_set::get_domain_size()
{
	return domain_size;
}

double credal_set::get_PrC(uint16 extreme_point, uint16 val)
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

interval_distribution::interval_distribution(uint16 new_domain_size, double* new_PrL, double* new_PrU) : uncertainty_model(MT_INTERVAL)
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

interval_distribution::interval_distribution(interval_distribution& existing_model) : uncertainty_model(existing_model)
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
	uncertainty_model::operator=(existing_model);
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

Dempster_Shafer_model::Dempster_Shafer_model(uint16 new_domain_size, double* new_m) : uncertainty_model(MT_DS)
{
	domain_size = new_domain_size;
	num_of_sets = 1 << domain_size;
	for (uint32 i = 0; i < num_of_sets; i++)
	{
		m[i] = new_m[i];
	}
	normalize();
}

Dempster_Shafer_model::Dempster_Shafer_model(Dempster_Shafer_model& existing_model) : uncertainty_model(existing_model)
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
	uncertainty_model::operator=(existing_model);
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


fuzzy_distribution::fuzzy_distribution(uint16 new_domain_size, fuzzy_values* new_PrF) : uncertainty_model(MT_FUZZY)
{
	domain_size = new_domain_size;
	PrF = new fuzzy_values[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrF[i] = new_PrF[i];
	}
}

fuzzy_distribution::fuzzy_distribution(fuzzy_distribution& existing_model) : uncertainty_model(existing_model.the_model_type)
{
	domain_size = existing_model.domain_size;
	PrF = new fuzzy_values[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrF[i] = existing_model.PrF[i];
	}
}

fuzzy_distribution& fuzzy_distribution::operator=(fuzzy_distribution& existing_model)
{
	uncertainty_model::operator=(existing_model);
	delete[] PrF;
	domain_size = existing_model.domain_size;
	PrF = new fuzzy_values[domain_size];
	for (uint16 i = 0; i < domain_size; i++)
	{
		PrF[i] = existing_model.PrF[i];
	}
	return *this;
}

fuzzy_distribution* fuzzy_distribution::copy()
{
	return new fuzzy_distribution(*this);
}

fuzzy_distribution::~fuzzy_distribution()
{
	delete[] PrF;
}

uint16 fuzzy_distribution::get_domain_size()
{
	return domain_size;
}

fuzzy_values fuzzy_distribution::get_PrF(uint16 val)
{
	return PrF[val];
}


