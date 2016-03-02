#ifndef __IMAGETRANSFORMER_H_INCLUDED__
#define __IMAGETRANSFORMER_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class ImageTransformer {

	public:
		virtual void transformImage(ImagesMatches& imgsMatches) = 0;
	};
}

#endif
