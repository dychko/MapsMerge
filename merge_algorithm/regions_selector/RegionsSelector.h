#ifndef __REGIONSSELECTOR_H_INCLUDED__
#define __REGIONSSELECTOR_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class RegionsSelector {

	public:
		virtual void selectRegions(ImagesMatches& imgMatches) = 0;

		void leaveRegionsMatches(ImagesMatches& imgMatches);

	};
}

#endif