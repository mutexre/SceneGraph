//
//  Created by mutexre on 08/01/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

namespace SG
{
    vector<char>
    loadImage(const char* path,
              unsigned& w, unsigned& h, unsigned& bytesPerRow,
              ColorComponents& colorComponents,
              PixelDataType& pixelDataType,
              bool flipVertical,
              bool flipHorizontal);

    class Image
    {
    public:
        enum class StorageType
        {
            internal,
            external
        };
        
    private:
        unsigned w, h;
        unsigned bytesPerRow;
        ColorComponents components;
        PixelDataType dataType;
        
        struct {
            StorageType type;
            vector<char> internal;
            char* external;
        }
        storage;
        
        char* data;

    private:
        static size_t calcDataSize(unsigned w, unsigned h,
                                   ColorComponents,
                                   PixelDataType,
                                   Option<int> bytesPerRow = Option<int>());
        
        void resizeInternalStorage(unsigned w, unsigned h);

    public:
        Image();
        Image(const char* path, bool flipVertical, bool flipHorizontal);
        Image(const string& path, bool flipVertical, bool flipHorizontal);
        
        Image(char* data, int w, int h,
              ColorComponents, PixelDataType,
              Option<int> bytesPerRow = Option<int>(),
              bool copyDataToInternalStorage = false);
        
        virtual ~Image();

        void init(unsigned w, unsigned h, ColorComponents, PixelDataType, Option<int> bytesPerRow = Option<int>());
        
        void setExternalStorage(char*);
        
        void copyExternalDataToInternalStorage(const char* data, int w, int h,
                                               ColorComponents, PixelDataType,
                                               Option<int> bytesPerRow = Option<int>());

        void copyDataToInternalStorage();

        StorageType getStorageType() const;

        unsigned getW() const;
        unsigned getH() const;
        unsigned getBytesPerRow() const;

        ColorComponents getColorComponents() const;
        PixelDataType getPixelDataType() const;

        const char* getData() const;
        char* getData();

        bool resample(unsigned w, unsigned h);
        shared_ptr<Image> getResampledImage(unsigned w, unsigned h) const;
        
        mat3 calcPaddingUvTransform() const;
    };
}
