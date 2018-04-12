//
//  Created by mutexre on 12/06/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

namespace SG
{
    template <typename T = Image>
    class ImagePyramid
    {
    protected:
        std::vector<std::shared_ptr<T>> images;
    
    protected:
        static unsigned calcNumberOfLevels(const std::shared_ptr<T>& image);
    
    public:
        ImagePyramid();
        ImagePyramid(const std::shared_ptr<T>&, Option<unsigned> levelCount = Option<unsigned>());
        
        ImagePyramid(const ImagePyramid&) = default;
        ImagePyramid& operator=(ImagePyramid&) = default;
        
        ImagePyramid(ImagePyramid&&) = default;
        ImagePyramid& operator=(ImagePyramid&&) = default;
        
        virtual ~ImagePyramid();
        
        void init(const std::shared_ptr<T>&, Option<unsigned> levelCount = Option<unsigned>());
        
        const std::vector<std::shared_ptr<T>>& getImages() const;
    };
    
    #include <SceneGraph/ImagePyramidDefinition.hpp>
}
