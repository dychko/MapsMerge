#ifndef __IMAGESMERGER_H_INCLUDED__
#define __IMAGESMERGER_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class ImagesMerger {

	public:
		virtual void mergeImages(ImagesMatches& imgsMatches) = 0;

	};
}

#endif
