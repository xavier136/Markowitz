#ifndef BackTest_h
#define BackTest_h

#include "../Headers/Matrix.h"
#include "../Headers/Portfolio.h"
#include "../Headers/Markowitz.h"


class BackTest
{
	public:
		BackTest(int num_assets_, int num_returns_, int in_sample_size_, int out_sample_size_, Vector& target_returns_, double accuracy_, int iterations_)
		{ 
			num_assets = num_assets_;
			num_returns = num_returns_;
			in_sample_size = in_sample_size_;
			out_sample_size = out_sample_size_;
			target_returns = target_returns_;
			accuracy = accuracy_;
			iterations = iterations_;
		};
		void getData();
		void deleteData();
		void initBackTest();
		void runBackTest();
		double **get_returnData() { return returnData; };
		int get_num_assets() { return num_assets; };
		int get_num_returns() { return num_returns; };

	private:
		int num_assets;
		int num_returns;
		int in_sample_size;
		int out_sample_size;
		Vector target_returns;
		vector<Portfolio> portfolios;
		double **returnData;
		double accuracy;
		double iterations;
};

#endif
