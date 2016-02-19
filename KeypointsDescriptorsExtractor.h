#ifndef __KEYPOINTSDESCRIPTORSEXTRACTOR_H_INCLUDED__
#define __KEYPOINTSDESCRIPTORSEXTRACTOR_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class KeypointsDescriptorsExtractor {

	public:
		virtual void detectAndCompute(ImagesMatches& imgsMatches) = 0;
	};
}

#endif
