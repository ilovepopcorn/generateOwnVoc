#include "generateVoc.h"
#include <dirent.h>

#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>

void LoadImages(const std::string &strPathToSequence, std::vector<std::string> &strImage);

void LoadImages(const std::string& strPathToSequence, std::vector< std::string >& strImage)
{
    std::string absolutePath = strPathToSequence;
    DIR* dir = opendir(absolutePath.c_str());
    struct dirent* ptr; 
    while ((ptr = readdir(dir)) != NULL) {
       //if(ptr->d_name != "." && ptr->d_name != "..")
        if (strcmp(ptr->d_name,".") != 0 && strcmp(ptr->d_name,"..") != 0) {
             std::string subDirect = strPathToSequence;
             if(ptr->d_type == 8) {
                //cout<<ptr->d_name<<endl;
                std::string loadPath = subDirect + "/";
                loadPath += ptr->d_name;
		//std::cout<<loadPath<<std::endl;
                strImage.push_back(loadPath);

            }
        }
    }
}


void myOwnVocabulary::initAndExtractORB(const std::string& strPathToSequence,const std::string& settingFile)
{ 
    std::vector<std::string> Images;
    LoadImages(strPathToSequence,Images);
    std::cout<<"total " << Images.size()<<" images"<<std::endl;
  
    cv::FileStorage fSettings(settingFile, cv::FileStorage::READ);
    
    int FeatureNum = fSettings["ORBextractor.nFeatures"];
    std::cout<<FeatureNum<<std::endl;
    float ScaleFactor = fSettings["ORBextractor.scaleFactor"];
    int Levels = fSettings["ORBextractor.nLevels"];
    int IniThFAST = fSettings["ORBextractor.iniThFAST"];
    int MinThFAST = fSettings["ORBextractor.minThFAST"];
    
    orbExtractor = new ORBextractor(FeatureNum,ScaleFactor,Levels,IniThFAST,MinThFAST);
    
    cv::Mat im;
    for(int i = 0;i < Images.size(); ++i){
       im = cv::imread(Images[i],cv::IMREAD_GRAYSCALE);
       
       if(im.empty()) {
            std::cerr << endl << "Failed to load image at: " << string(Images[i]) << std::endl;
            return;
        }
        //extract orb features
        std::vector<cv::KeyPoint> keyPoints;
	cv::Mat descriptors;
	//descriptors of an image
        (*orbExtractor)(im,cv::Mat(),keyPoints,descriptors);
	if (descriptors.empty())
	  std::cerr<<"wrong descriptors"<<std::endl;
	vector<cv::Mat> CurrentDesc = toDescriptorVector(descriptors);
	if(CurrentDesc.empty())
	    std::cerr << "descriptors empty"<<string(Images[i]) <<std::endl;
	training_features.push_back(CurrentDesc);
    }
    
}

void myOwnVocabulary::createVocabulary(const std::string& vocSavePath)
{
  
   if(!training_features.empty()){
       std::cout<<training_features.size()<< " "<<training_features[0].size()<<std::endl;
       ORBVocabulary.create(training_features,10,5);//modify before use
       ORBVocabulary.saveToTextFile(vocSavePath);
   } else
        std::cerr <<"features empty" <<std::endl;
     
   
   
   return;

}

std::vector< cv::Mat > myOwnVocabulary::toDescriptorVector(const cv::Mat& Descriptors)
{
    std::vector<cv::Mat> vDesc;
    vDesc.reserve(Descriptors.rows);
    for (int j=0;j<Descriptors.rows;j++)
        vDesc.push_back(Descriptors.row(j));

    return vDesc;

}
