//
//  Created by mutexre on 14/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG
{
    class Material : public virtual Object
    {
    protected:
        shared_ptr<Context> context;
        shared_ptr<Program> program;
    
    protected:
        void bindProgram();
        
        virtual void invalidateVariables();
        virtual void syncTextureSamplers();
        virtual void syncVariables();
        virtual void activateTextures();

    public:
        Material(const shared_ptr<Context>&);
        virtual ~Material();

        const shared_ptr<Context>& getContext() const;
        void setContext(const shared_ptr<Context>&);

        const shared_ptr<Program>& getProgram() const;
        void setProgram(const shared_ptr<Program>&);

        bool isProgramShared() const;

        virtual void bind();

        bool isVertexAttributeActive(const string&);
        bool isParameterActive(const string&);

        virtual void set(const string& var, float);
        virtual void set(const string& var, float, float);
        virtual void set(const string& var, float, float, float);
        virtual void set(const string& var, float, float, float, float);
        virtual void set(const string& var, unsigned size, unsigned count, const float*);

        virtual void set(const string& var, int);
        virtual void set(const string& var, int, int);
        virtual void set(const string& var, int, int, int);
        virtual void set(const string& var, int, int, int, int);
        virtual void set(const string& var, unsigned size, unsigned count, const int*);

        virtual void set(const string& var, unsigned);
        virtual void set(const string& var, unsigned, unsigned);
        virtual void set(const string& var, unsigned, unsigned, unsigned);
        virtual void set(const string& var, unsigned, unsigned, unsigned, unsigned);
        virtual void set(const string& var, unsigned size, unsigned count, const unsigned*);

        virtual void set(const string& var, const mat2&, bool transpose = false);
        virtual void set(const string& var, const mat3&, bool transpose = false);
        virtual void set(const string& var, const mat4&, bool transpose = false);
        virtual void set(const string& var, const mat2x3&, bool transpose = false);
        virtual void set(const string& var, const mat3x2&, bool transpose = false);
        virtual void set(const string& var, const mat2x4&, bool transpose = false);
        virtual void set(const string& var, const mat4x2&, bool transpose = false);
        virtual void set(const string& var, const mat3x4&, bool transpose = false);
        virtual void set(const string& var, const mat4x3&, bool transpose = false);

        virtual void set(const string& var, unsigned count, const mat2*, bool transpose = false);
        virtual void set(const string& var, unsigned count, const mat3*, bool transpose = false);
        virtual void set(const string& var, unsigned count, const mat4*, bool transpose = false);
        virtual void set(const string& var, unsigned count, const mat2x3*, bool transpose = false);
        virtual void set(const string& var, unsigned count, const mat3x2*, bool transpose = false);
        virtual void set(const string& var, unsigned count, const mat2x4*, bool transpose = false);
        virtual void set(const string& var, unsigned count, const mat4x2*, bool transpose = false);
        virtual void set(const string& var, unsigned count, const mat3x4*, bool transpose = false);
        virtual void set(const string& var, unsigned count, const mat4x3*, bool transpose = false);
    };
}
