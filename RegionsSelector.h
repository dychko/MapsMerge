#ifndef __REGIONSSELECTOR_H_INCLUDED
#define __REGIONSSELECTOR_H_INCLUDED

class ImagesMatches;

namespace MapsMerge {
	class RegionsSelector {

	public:
		virtual void selectRegions(ImagesMatches& imgMatches) = 0;

		void leaveRegionsMatches(ImagesMatches& imgMatches);

	};
}

#endif
