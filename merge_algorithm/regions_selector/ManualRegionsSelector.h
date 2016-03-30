#ifndef __MANUALREGIONSSELECTOR_H_INCLUDED__
#define __MANUALREGIONSSELECTOR_H_INCLUDED__

#include "RegionsSelector.h"
#include "opencv2/core/core.hpp"

class ImagesMatches;

namespace MapsMerge {
	class ManualRegionsSelector : public MapsMerge::RegionsSelector {
	
	private:
		static Point P1;
		static Point P2;
		static Rect cropRect;
		static bool clicked;

		static string winName1;
		static string winName2;

		static Mat img1;
		static Mat img2;

		static void showImage(Mat img, string winName, Rect cropRect);
		static void checkBoundary(Rect& cropRect, Mat& img);
		static void onMouse(int event, int x, int y, int f, void* numWindow);

	public:
		ManualRegionsSelector() {};

		void selectRegions(ImagesMatches& imgMatches);
	};
}

#endif
