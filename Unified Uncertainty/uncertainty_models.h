

#ifndef __UNCERTAINTY_MODELS_H__
#define __UNCERTAINTY_MODELS_H__

typedef unsigned short uint16;
typedef unsigned long uint32;

#define MAX(a,b) (a >= b) ? a : b
#define MIN(a,b) (a <= b) ? a : b

#include <cstdlib>


enum model_type {MT_CRISP, MT_EPSILON, MT_PROBABILITY, MT_CREDAL, MT_FUZZY};

enum credal_set_type {CST_LIST, CST_INTERVAL, CST_DS};

enum fuzzy_model_type {FMT_PROBABILITY, FMT_SEMANTIC};

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
protected:
	credal_set_type the_credal_set_type;
public:
	credal_set(credal_set_type new_credal_set_type);
	credal_set(credal_set& existing_model);
	credal_set& operator=(credal_set& existing_model);
	virtual credal_set* copy();
	~credal_set();
	credal_set_type get_credal_set_type();
};

class extreme_points : public credal_set
{
	uint16 domain_size;
	uint16 num_of_extreme_points;
	double** PrC;

	void normalize();
public:
	extreme_points(uint16 new_domain_size, uint16 new_num_of_extreme_points, double** new_PrC); // A deep copy is used.
	extreme_points(extreme_points& existing_model); // A deep copy is used.
	extreme_points& operator=(extreme_points& existing_model); // A deep copy is used.
	virtual extreme_points* copy();
	~extreme_points();
	uint16 get_domain_size();
	double get_PrC(uint16 extreme_point, uint16 val);
};

class interval_distribution : public credal_set
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

class Dempster_Shafer_model : public credal_set
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

class fuzzy_model : public uncertainty_model
{
protected:
	fuzzy_model_type the_fuzzy_model_type;
public:
	fuzzy_model(fuzzy_model_type new_fuzzy_model_type);
	fuzzy_model(fuzzy_model& existing_model);
	fuzzy_model& operator=(fuzzy_model& existing_model);
	virtual fuzzy_model* copy();
	~fuzzy_model();
	fuzzy_model_type get_fuzzy_model_type();
};

class fuzzy_probability_distribution : public fuzzy_model
{
	uint16 domain_size;
	double* l;
	double* c;
	double* u;

	void normalize();
public:
	fuzzy_probability_distribution(uint16 new_domain_size, double* new_l, double* new_c, double* new_u); // A deep copy is used.
	fuzzy_probability_distribution(fuzzy_probability_distribution& existing_model); // A deep copy is used.
	fuzzy_probability_distribution& operator=(fuzzy_probability_distribution& existing_model); // A deep copy is used.
	virtual fuzzy_probability_distribution* copy();
	~fuzzy_probability_distribution();
	uint16 get_domain_size();
	double get_l(uint16 val);
	double get_c(uint16 val);
	double get_u(uint16 val);
};

enum semantic_values {FV_0S, FV_1S, FV_0W, FV_1W, FV_H, FV_U};

class semantic_distribution : public fuzzy_model
{
	uint16 domain_size;
	semantic_values* PrS;

public:
	semantic_distribution(uint16 new_domain_size, semantic_values* new_PrF); // A deep copy is used.
	semantic_distribution(semantic_distribution& existing_model); // A deep copy is used.
	semantic_distribution& operator=(semantic_distribution& existing_model); // A deep copy is used.
	virtual semantic_distribution* copy();
	~semantic_distribution();
	uint16 get_domain_size();
	semantic_values get_PrS(uint16 val);
};



#endif
