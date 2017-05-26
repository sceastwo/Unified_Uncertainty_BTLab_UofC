

#ifndef __UNCERTAINTY_MODELS_H__
#define __UNCERTAINTY_MODELS_H__

typedef unsigned short uint16;
typedef unsigned long uint32;

#define MAX(a,b) (a >= b) ? a : b
#define MIN(a,b) (a <= b) ? a : b

#include <cstdlib>


enum model_type {MT_CRISP, MT_EPSILON, MT_PROBABILITY, MT_CREDAL, MT_INTERVAL, MT_DS, MT_FUZZY};

class uncertainty_model
{
protected:
	model_type the_model_type;
public:
	uncertainty_model(model_type new_model_type);
	uncertainty_model(uncertainty_model& existing_model);
	uncertainty_model& operator=(uncertainty_model& existing_model);
	virtual uncertainty_model* copy();
	model_type get_model_type();
};

class crisp_value : public uncertainty_model
{
	uint16 the_val;
public:
	crisp_value(uint16 new_val);
	crisp_value(crisp_value& existing_model);
	crisp_value& operator=(crisp_value& existing_model);
	virtual crisp_value* copy();
	uint16 get_val();
};

class epsilon : public uncertainty_model
{
public:
	epsilon();
	epsilon(epsilon& existing_model);
	epsilon& operator=(epsilon& existing_model);
	virtual epsilon* copy();
};

class probability_distribution : public uncertainty_model
{
	uint16 domain_size;
	double* Pr;

	void normalize();
public:
	probability_distribution(uint16 new_domain_size, double* new_Pr); // A deep copy is used.
	probability_distribution(probability_distribution& existing_model); // A deep copy is used.
	probability_distribution& operator=(probability_distribution& existing_model); // A deep copy is used.
	virtual probability_distribution* copy();
	~probability_distribution();
	uint16 get_domain_size();
	double get_Pr(uint16 val);
	void set_Pr(uint16 val, double new_Pr);
	void set_Pr(double* new_Pr); // A deep copy is used.
};

class credal_set : public uncertainty_model
{
	uint16 domain_size;
	uint16 num_of_extreme_points;
	double** PrC;

	void normalize();
public:
	credal_set(uint16 new_domain_size, uint16 new_num_of_extreme_points, double** new_PrC); // A deep copy is used.
	credal_set(credal_set& existing_model); // A deep copy is used.
	credal_set& operator=(credal_set& existing_model); // A deep copy is used.
	virtual credal_set* copy();
	~credal_set();
	uint16 get_domain_size();
	double get_PrC(uint16 extreme_point, uint16 val);
};

class interval_distribution : public uncertainty_model
{
	uint16 domain_size;
	double* PrL;
	double* PrU;

	void normalize();
public:
	interval_distribution(uint16 new_domain_size, double* new_PrL, double* new_PrU); // A deep copy is used.
	interval_distribution(interval_distribution& existing_model); // A deep copy is used.
	interval_distribution& operator=(interval_distribution& existing_model); // A deep copy is used.
	virtual interval_distribution* copy();
	~interval_distribution();
	uint16 get_domain_size();
	double get_PrL(uint16 val);
	double get_PrU(uint16 val);
};

class Dempster_Shafer_model : public uncertainty_model
{
	uint16 domain_size; //The domain size cannot exceed 31.
	uint32 num_of_sets; 
	double* m; //m[0] will denote the weight of the empty set,  which is always 0.0.

	void normalize();
public:
	Dempster_Shafer_model(uint16 new_domain_size, double* new_m); // A deep copy is used.
	Dempster_Shafer_model(Dempster_Shafer_model& existing_model); // A deep copy is used.
	Dempster_Shafer_model& operator=(Dempster_Shafer_model& existing_model); // A deep copy is used.
	virtual Dempster_Shafer_model* copy();
	~Dempster_Shafer_model();
	uint16 get_domain_size();
	double get_m(uint32 set);
};

enum fuzzy_values {FV_0S, FV_1S, FV_0W, FV_1W, FV_H, FV_U};

class fuzzy_distribution : public uncertainty_model
{
	uint16 domain_size;
	fuzzy_values* PrF;

public:
	fuzzy_distribution(uint16 new_domain_size, fuzzy_values* new_PrF); // A deep copy is used.
	fuzzy_distribution(fuzzy_distribution& existing_model); // A deep copy is used.
	fuzzy_distribution& operator=(fuzzy_distribution& existing_model); // A deep copy is used.
	virtual fuzzy_distribution* copy();
	~fuzzy_distribution();
	uint16 get_domain_size();
	fuzzy_values get_PrF(uint16 val);
};



#endif
