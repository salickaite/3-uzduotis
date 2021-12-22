#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::istream;
using std::cout;
using std::cin;
using std::endl;

class Zmogus
{
protected:
	string vardas_;
	string pavarde_;
public:
	Zmogus()
	{
		vardas_ = "";
		pavarde_ = "";
	}

	virtual string vardas() = 0;
	virtual string pavarde() = 0;
	~Zmogus() {};
};


class Studentas : public Zmogus
{
private:
	int egz_;
	float gal_vid_;
	vector<float> nd_;

public:
	Studentas()
	{
		egz_ = 0;
		gal_vid_ = 0;
		nd_.clear();
	}

	Studentas(string, string, float);
	Studentas(const Studentas& st);
	Studentas& operator=(const Studentas& st);

	inline string vardas() { return vardas_; }
	inline string pavarde() { return pavarde_; }
	inline int egz() const { return egz_; }
	inline vector<float> nd() const { return nd_; }
	inline float gal_vid() const { return gal_vid_; }

	void setVardas(string);
	void setPavarde(string);
	void setEgz(int);
	void setND(vector<float>);
	void setGal_vid(float);
	~Studentas()
	{
		nd_.clear();
	}

	void pild();
	float vidurkis();
	float galBalas(const char);
	static void nuskaitymas_v_(string read);
	static void padalijimas3_(vector<Studentas>& vec);
	static bool pred_(const Studentas& st);
	static void isvedimas_(vector<Studentas>& vec, string pav);

	friend std::ostream& operator<<(std::ostream& out, const Studentas& a);
	friend bool operator==(const Studentas& a, const Studentas& b);
};