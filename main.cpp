#include <iostream>

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>

#include "generateVoc.h"

int main(int argc, char **argv) {
    std:cout<<"Usage  : ./generateownvoc PATH_IMAGE_SEQUENCE PATH_SETTINGFILE PATH_VOC_SAVE_PATH"<<std::endl;
    const std::string strPathToSequence = argv[1];
    //std::cout<<strPathToSequence<<std::endl;
    const std::string settingFile =argv[2];
    //std::cout<<settingFile<<std::endl;
    const std::string vocSavePath = argv[3];//TO RESURE
   // std::cout<<vocSavePath<<std::endl;
    myOwnVocabulary myvoc;
    myvoc.initAndExtractORB(strPathToSequence,settingFile);
    myvoc.createVocabulary(vocSavePath);
    return 0;
}
