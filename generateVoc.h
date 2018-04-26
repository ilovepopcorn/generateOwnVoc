#ifndef GENERATE_VOC_H
#define GENERATE_VOC_H

#include "FORB.h"
#include "TemplatedVocabulary.h"

#include "ORBextractor.h"

#include <string>
class myOwnVocabulary{
public:
    
    void initAndExtractORB(const std::string& strPathToSequence,const std::string& settingFile);
    void createVocabulary(const std::string& vocSavePath);
    

  
private:
  
    std::vector<cv::Mat> toDescriptorVector(const cv::Mat &Descriptors);
    
private:
    
    DBoW2::TemplatedVocabulary<DBoW2::FORB::TDescriptor, DBoW2::FORB> ORBVocabulary;
    
    ORBextractor* orbExtractor;
    
    std::vector<std::vector<DBoW2::FORB::TDescriptor> > training_features;

  
  
  
};





#endif