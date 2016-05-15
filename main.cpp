#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#include "experiments\SomeExperiment.h"
#include "experiments\GeneralExperiment.h"
#include "experiments\RegionsMatchingExperiment.h"
#include "experiments\TransformationQualityExperiment.h"
#include "experiments\ClusteringExperiment.h"
#include "experiments\ClusteringSeriesExperiment.h"



using namespace cv;
using namespace std;
using namespace MapsMerge;

int main(int argc, char** argv) {

	AbstractExperiment *experiment = new ClusteringExperiment();
	experiment->run();

	return 0;
}
