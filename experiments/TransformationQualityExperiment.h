#ifndef __TRANSFORMATION_QUALITY_EXPERIMENT_H_INCLUDED__
#define __TRANSFORMATION_QUALITY_EXPERIMENT_H_INCLUDED__

#include "AbstractExperiment.h"
#include <string>

using namespace std;

namespace MapsMerge {
	class TransformationQualityExperiment : public MapsMerge::AbstractExperiment {
	private:
		string createImgName(string rootPath, string algName, int numRegions, int id, string type, string extension);

	public:
		void run();
	};
}

#endif
