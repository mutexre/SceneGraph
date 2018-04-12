//
//  Created by mutexre on 08/01/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

namespace SG
{
    class ImageStack
    {
    private:
        unsigned w, h;
        ColorComponents components;
        PixelDataType dataType;
        std::vector<std::shared_ptr<Image>> subImages;

    private:
        void updateStateBasedOnImage(const std::shared_ptr<Image>&);
        
    public:
        ImageStack();
        ImageStack(const std::vector<std::string>&, bool flipVertical, bool flipHorizontal);

        ImageStack(const ImageStack&) = default;
        ImageStack& operator=(ImageStack&) = default;
        
        ImageStack(ImageStack&&) = default;
        ImageStack& operator=(ImageStack&&) = default;

        virtual ~ImageStack();

        unsigned getW() const;
        unsigned getH() const;
        unsigned getD() const;

        ColorComponents getColorComponents() const;
        PixelDataType getPixelDataType() const;

        const char* getData(unsigned z) const;
        char* getData(unsigned z);

        const std::shared_ptr<Image>& operator[](unsigned z) const;

        void resample(unsigned w, unsigned h);
        std::shared_ptr<ImageStack> getResampledImage(unsigned w, unsigned h) const;
    };
}
