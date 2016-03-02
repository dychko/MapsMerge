#ifndef __DESCRIPTORSMATCHER_H_INCLUDED__
#define __DESCRIPTORSMATCHER_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class DescriptorsMatcher {

	public:
		virtual void matchDescriptors(ImagesMatches& imgsMatches) = 0;

	};
}

#endif
