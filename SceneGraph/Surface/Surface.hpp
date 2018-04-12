//
//  Created by mutexre on 18/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

namespace SG
{
    class Surface : public virtual Object
    {
    public:
        enum class AttachmentPoint {
            color,
            depth,
            stencil
        };
        
        enum class Target {
            read, draw
        };
    
    public:
        virtual ~Surface();
        
        virtual void attach(AttachmentPoint,
                            unsigned attachmentIndex,
                            const std::shared_ptr<Texture>&,
                            unsigned level = 0,
                            unsigned cubeMapSide = 0) = 0;
        
        void attach(AttachmentPoint,
                    const std::shared_ptr<SG::Texture>&,
                    unsigned level = 0,
                    unsigned cubeMapSide = 0);
        
        virtual void attach(AttachmentPoint,
                            unsigned attachmentIndex,
                            const std::shared_ptr<Renderbuffer>&) = 0;
        
        void attach(AttachmentPoint, const std::shared_ptr<Renderbuffer>&);
        
        virtual void detach(AttachmentPoint, unsigned attachmentIndex = 0) = 0;
        
        virtual void makeActive(Target) = 0;
        virtual void makeActive();
        
        virtual void read(unsigned x, unsigned y, unsigned w, unsigned h,
                          ColorComponents, PixelDataType,
                          void* data) = 0;
        
        virtual void invalidate(Target) = 0;
        virtual void invalidate();
    };
}
