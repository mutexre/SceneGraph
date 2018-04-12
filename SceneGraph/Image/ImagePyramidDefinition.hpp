//
//  Created by mutexre on 12/06/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

template <typename T>
ImagePyramid<T>::ImagePyramid()
{}

template <typename T>
ImagePyramid<T>::ImagePyramid(const std::shared_ptr<T>& image, Option<unsigned> levelCount) {
    init(image, levelCount);
}

template <typename T>
ImagePyramid<T>::~ImagePyramid()
{}

template <typename T>
unsigned ImagePyramid<T>::calcNumberOfLevels(const std::shared_ptr<T>& image)
{
    int w = image->getW();
    int h = image->getH();
    auto minDim = std::min(w, h);
    
    unsigned reminder = minDim;
    unsigned log2 = 0;
    while ((reminder & 1) == 0) {
        reminder >>= 1;
        log2++;
    }
    
    assert(reminder == 1);
    
    return log2;
}

template <typename T>
void ImagePyramid<T>::init(const std::shared_ptr<T>& image, Option<unsigned> levelCount)
{
    images.clear();
    images.push_back(image);
    
    if (!levelCount.defined)
        levelCount = calcNumberOfLevels(image);
    
    if (levelCount.value > 0)
    {
        auto w = image->getW();
        auto h = image->getH();
        
        auto currentImage = image;
        for (auto i = 0; i < levelCount.value; i++)
        {
            w >>= 1;
            h >>= 1;
            
            currentImage = currentImage->getResampledImage(w, h);
            images.push_back(currentImage);
        }
    }
}

template <typename T>
const std::vector<std::shared_ptr<T>>& ImagePyramid<T>::getImages() const {
    return images;
}
