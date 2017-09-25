//
//  Created by mutexre on 04/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Texture : public virtual Object
    {
    public:
        enum class Type {
            t1d, t1d_array,
            t2d, t2d_array,
            t2d_ms, t2d_array_ms,
            t3d,
            cubemap, cubemapArray,
            rectangle,
            buffer,
            external
        };

        enum class MinFilter {
            nearest, nearest_MipmapNearest, nearest_MipmapLinear,
            linear, linear_MipmapNearest, linear_MipmapLinear
        };

        enum class MagFilter {
            nearest, linear
        };

        enum class Wrap {
            clamp_to_edge, clamp_to_border, repeat
        };

    protected:
        Type type;
        PixelFormat format;

        struct {
            MinFilter min = MinFilter::linear;
            MagFilter mag = MagFilter::linear;
        }
        filter;

        struct {
            Wrap s = Wrap::clamp_to_edge;
            Wrap t = Wrap::clamp_to_edge;
            Wrap r = Wrap::clamp_to_edge;
        }
        wrap;

        struct {
            float min = -1000;
            float max = +1000;
            float baseLevel = 0;
            float maxLevel = 1000;
        }
        lod;

        vec4 borderColor{0};
        float priority = 1;

    protected:
        virtual void setImages(const vector<shared_ptr<Image>>&) = 0;
        virtual void setImages(const vector<shared_ptr<Image3D>>&) = 0;

    public:
        Texture();
        Texture(Type, PixelFormat);
        virtual ~Texture();
        
        virtual void init(Texture::Type, PixelFormat) = 0;
        
        virtual void allocStorage(unsigned width,
                                  unsigned height,
                                  unsigned depth = 0,
                                  unsigned level = 0,
                                  unsigned layer = 0) = 0;
        
        virtual void allocImmutableStorage(unsigned width,
                                           unsigned height,
                                           unsigned depth = 0,
                                           unsigned levelsCount = 1,
                                           unsigned layersCount = 1) = 0;
        
        void setImage(const shared_ptr<Image>&);
        void setImage(const shared_ptr<Image3D>&);
        void setImage(Image&);
        
        virtual void setImage(const void* data,
                              unsigned width,
                              unsigned height,
                              unsigned depth = 0,
                              ColorComponents = ColorComponents::rgba,
                              PixelDataType = PixelDataType::u8,
                              unsigned level = 0,
                              unsigned layer = 0) = 0;

        virtual void setSubImage(const void* data,
                                 unsigned x,
                                 unsigned y,
                                 unsigned z,
                                 unsigned width,
                                 unsigned height,
                                 unsigned depth,
                                 ColorComponents = ColorComponents::rgba,
                                 PixelDataType = PixelDataType::u8,
                                 unsigned level = 0,
                                 unsigned layer = 0) = 0;
        
        template <typename T>
        void setImages(const shared_ptr<ImagePyramid<T>>&);

        virtual void bind(unsigned short target = 0) = 0;
        
        virtual void generateMipmap() = 0;

        Type getType() const;
        void setType(Type);

        PixelFormat getFormat() const;
        void setFormat(PixelFormat f);

        MinFilter getMinFilter() const;
        void setMinFilter(MinFilter f);

        MagFilter getMagFilter() const;
        void setMagFilter(MagFilter f);

        Wrap getWrapS() const;
        void setWrapS(Wrap w);

        Wrap getWrapT() const;
        void setWrapT(Wrap w);

        Wrap getWrapR() const;
        void setWrapR(Wrap w);

        float getMinLod() const;
        void setMinLod(float);
        
        float getMaxLod() const;
        void setMaxLod(float);
        
        float getBaseLevel() const;
        void setBaseLevel(float);
        
        float getMaxLevel() const;
        void setMaxLevel(float);

        vec4 getBorderColor() const;
        void setBorderColor(vec4 c);

        float getPriority() const;
        void setPriority(float p);
    };
    
    template <typename T>
    void Texture::setImages(const shared_ptr<ImagePyramid<T>>& imagePyramid) {
        setImages(imagePyramid->getImages());
    }
}
