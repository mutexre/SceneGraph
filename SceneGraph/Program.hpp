//
//  Created by mutexre on 26/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Program : public virtual Object
    {
        friend class Context;
        friend class Material;
        
    public:
        struct Source {
            string vertex, geometry, fragment;
        };

        struct Binary {
            vector<char> data;
        };

    protected:
        int useCount = 0;
        Source sources;
        shared_ptr<Binary> binary;
    
    protected:
        virtual void loadBinary() = 0;
        virtual void bind() = 0;

    public:
        virtual ~Program();
        
        int getUseCount() const;
        void adjustUseCount(int amount);
        
        shared_ptr<Binary> getBinary();
        
        virtual bool isVertexAttributeActive(const string&) = 0;
        virtual bool isUniformActive(const string&) = 0;
        
        virtual unsigned getVertexAttributeLocation(const string&) = 0;
        virtual unsigned getUniformLocation(const string&) = 0;

        virtual void set(const string& var, float);
        virtual void set(const string& var, float, float);
        virtual void set(const string& var, float, float, float);
        virtual void set(const string& var, float, float, float, float);
        virtual void set(const string& var, unsigned size, unsigned count, const float*) = 0;

        virtual void set(const string& var, const vec2&);
        virtual void set(const string& var, const vec3&);
        virtual void set(const string& var, const vec4&);

        virtual void set(const string& var, int);
        virtual void set(const string& var, int, int);
        virtual void set(const string& var, int, int, int);
        virtual void set(const string& var, int, int, int, int);
        virtual void set(const string& var, unsigned size, unsigned count, const int*) = 0;

        virtual void set(const string& var, const ivec2&);
        virtual void set(const string& var, const ivec3&);
        virtual void set(const string& var, const ivec4&);

        virtual void set(const string& var, unsigned);
        virtual void set(const string& var, unsigned, unsigned);
        virtual void set(const string& var, unsigned, unsigned, unsigned);
        virtual void set(const string& var, unsigned, unsigned, unsigned, unsigned);
        virtual void set(const string& var, unsigned size, unsigned count, const unsigned*) = 0;

        virtual void set(const string& var, const uvec2&);
        virtual void set(const string& var, const uvec3&);
        virtual void set(const string& var, const uvec4&);

        virtual void set(const string& var, const mat2&, bool transpose = false);
        virtual void set(const string& var, const mat3&, bool transpose = false);
        virtual void set(const string& var, const mat4&, bool transpose = false);
        virtual void set(const string& var, const mat2x3&, bool transpose = false);
        virtual void set(const string& var, const mat3x2&, bool transpose = false);
        virtual void set(const string& var, const mat2x4&, bool transpose = false);
        virtual void set(const string& var, const mat4x2&, bool transpose = false);
        virtual void set(const string& var, const mat3x4&, bool transpose = false);
        virtual void set(const string& var, const mat4x3&, bool transpose = false);

        virtual void set(const string& var, unsigned count, const mat2*, bool transpose = false) = 0;
        virtual void set(const string& var, unsigned count, const mat3*, bool transpose = false) = 0;
        virtual void set(const string& var, unsigned count, const mat4*, bool transpose = false) = 0;
        virtual void set(const string& var, unsigned count, const mat2x3*, bool transpose = false) = 0;
        virtual void set(const string& var, unsigned count, const mat3x2*, bool transpose = false) = 0;
        virtual void set(const string& var, unsigned count, const mat2x4*, bool transpose = false) = 0;
        virtual void set(const string& var, unsigned count, const mat4x2*, bool transpose = false) = 0;
        virtual void set(const string& var, unsigned count, const mat3x4*, bool transpose = false) = 0;
        virtual void set(const string& var, unsigned count, const mat4x3*, bool transpose = false) = 0;
    };
}
