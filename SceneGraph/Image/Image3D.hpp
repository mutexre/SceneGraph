//
//  Created by mutexre on 08/01/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

namespace SG
{
    class Image3D
    {
    private:
        unsigned w, h;
        ColorComponents components;
        PixelDataType dataType;
        vector<shared_ptr<Image>> subImages;

    public:
        Image3D();
        Image3D(const vector<string>&);
        virtual ~Image3D();

        Image3D(const Image3D&);

        unsigned getW() const;
        unsigned getH() const;
        unsigned getD() const;

        ColorComponents getColorComponents() const;
        PixelDataType getPixelDataType() const;

        const char* getData(unsigned z) const;
        char* getData(unsigned z);

        const shared_ptr<Image>& operator[](unsigned z) const;

        void resample(unsigned w, unsigned h);
        shared_ptr<Image3D> getResampledImage(unsigned w, unsigned h) const;
    };
}
