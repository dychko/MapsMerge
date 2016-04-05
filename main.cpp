#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#include "experiments\RegionsMatchingExperiment.h"
#include "experiments\GeneralExperiment.h"


using namespace cv;
using namespace std;
using namespace MapsMerge;

int main(int argc, char** argv) {

	AbstractExperiment *experiment = new RegionsMatchingExperiment();
	experiment->run();

	return 0;
}
