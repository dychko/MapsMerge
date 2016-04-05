#ifndef __REGIONSSELECTOR_H_INCLUDED__
#define __REGIONSSELECTOR_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class RegionsSelector {

	public:
		virtual void selectRegions(ImagesMatches& imgMatches) = 0;

		static vector<DMatch> leaveRegionsMatches(ImagesMatches&, vector<Rect>, vector<Rect>);

	};
}

#endif
