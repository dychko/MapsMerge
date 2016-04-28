#include "MapsMerger.h"

void MapsMerge::MapsMerger::readImages(string imgPath1, string imgPath2) {
	imagesMatches.readImages(imgPath1, imgPath2);
}

void MapsMerge::MapsMerger::showImages(string winName1, string winName2) {
	imagesMatches.showImages(winName1, winName2);
}

void MapsMerge::MapsMerger::showKeypoints(string winName1, string winName2) {
	imagesMatches.showKeypoints(winName1, winName2);
}

void MapsMerge::MapsMerger::showRegions(string winName1, string winName2) {
	imagesMatches.showRegions(winName1, winName2);
}

void MapsMerge::MapsMerger::showClusters(string winName1, string winName2) {
	imagesMatches.showClusters(winName1, winName2);
}

void MapsMerge::MapsMerger::writeRegions(string fileName1, string fileName2) {
	imagesMatches.writeRegions(fileName1, fileName2);
}

void MapsMerge::MapsMerger::setKeypointsDescriptorsExtractor(KeypointsDescriptorsExtractor* e) {
	keypointsDescriptorsExtractor = e;
}

void MapsMerge::MapsMerger::detectAndCompute() {
	keypointsDescriptorsExtractor->detectAndCompute(imagesMatches);
}

string MapsMerge::MapsMerger::getExtractorAlgName() {
	return keypointsDescriptorsExtractor->getAlgName();
}

void MapsMerge::MapsMerger::setDescriptorMatcher(DescriptorsMatcher* d) {
	descriptorsMatcher = d;
}

void MapsMerge::MapsMerger::matchDescriptors() {
	descriptorsMatcher->matchDescriptors(imagesMatches);
}

void MapsMerge::MapsMerger::showMatches(string winName) {
	imagesMatches.showMatches(winName);
}

void MapsMerge::MapsMerger::showGoodMatches(string winName) {
	imagesMatches.showGoodMatches(winName);
}

void MapsMerge::MapsMerger::setRegionsSelector(RegionsSelector* s) {
	regionsSelector = s;
}

void MapsMerge::MapsMerger::selectRegions() {
	regionsSelector->selectRegions(imagesMatches);
}

void MapsMerge::MapsMerger::leaveRegionsMatches() {
	imagesMatches.goodMatches = regionsSelector->leaveRegionsMatches(
		imagesMatches,
		imagesMatches.imgFeatures1.regions, 
		imagesMatches.imgFeatures2.regions);
}

int MapsMerge::MapsMerger::getNumRegions() {
	return imagesMatches.imgFeatures1.regions.size();
}

void MapsMerge::MapsMerger::setRegionsMatcher(RegionsMatcher* m) {
	regionsMatcher = m;
}

void MapsMerge::MapsMerger::shuffleRegions() {
	regionsMatcher->shuffleRegions(imagesMatches);
}

void MapsMerge::MapsMerger::matchRegions() {
	regionsMatcher->matchRegions(imagesMatches);
}

void MapsMerge::MapsMerger::setImageTransformer(ImageTransformer* t) {
	imageTransformer = t;
}

void MapsMerge::MapsMerger::transformImage() {
	imageTransformer->transformImage(imagesMatches);
}

void MapsMerge::MapsMerger::showTransformedImage(string winName) {
	imagesMatches.showTransformedImage(winName);
}

void MapsMerge::MapsMerger::setImagesMerger(ImagesMerger* m) {
	imagesMerger = m;
}

void MapsMerge::MapsMerger::mergeImages() {
	imagesMerger->mergeImages(imagesMatches);
}

void MapsMerge::MapsMerger::showMergedImage(string winName) {
	imagesMatches.showMergedImage(winName);
}

void MapsMerge::MapsMerger::writeMergedImage(string fileName) {
	imagesMatches.writeMergedImage(fileName);
}

void MapsMerge::MapsMerger::setQualityEvaluator(QualityEvaluator* e) {
	qualityEvaluator = e;
}

void MapsMerge::MapsMerger::evaluateQuality() {
	qualityEvaluator->evaluateQuality(imagesMatches);
}

void MapsMerge::MapsMerger::setRegionsByIndexes(vector<Rect>& savedRegions1, 
												vector<Rect>& savedRegions2, 
												vector<int>& regionsIndexes) {
	this->imagesMatches.imgFeatures1.regions.clear();
	this->imagesMatches.imgFeatures2.regions.clear();
	for (int i = 0; i < regionsIndexes.size(); i++) {
		this->imagesMatches.imgFeatures1.regions.push_back(savedRegions1[regionsIndexes[i]]);
		this->imagesMatches.imgFeatures2.regions.push_back(savedRegions2[regionsIndexes[i]]);
	}
}
