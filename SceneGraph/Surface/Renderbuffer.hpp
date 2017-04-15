//
//  Renderbuffer.hpp
//  sensee
//
//  Created by mutexre on 21/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

namespace SG
{
    class Renderbuffer : public virtual Object
    {
    protected:
        uvec2 size;
        PixelFormat format;
    
    public:
        virtual ~Renderbuffer();
        
        virtual void makeActive() = 0;
        
        uvec2 getSize() const;
        
        PixelFormat getFormat() const;
        void setFormat(PixelFormat);
    };
    
    class OffScreenBuffer : public virtual Renderbuffer
    {
    public:
        virtual void allocStorage(int w, int h,
                                  PixelFormat = PixelFormat::rgba8,
                                  int samples = 1) = 0;
    };
}
