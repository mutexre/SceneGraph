//
//  Created by mutexre on 14/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG
{
    class Material : public Object
    {
    protected:
        std::shared_ptr<Context> context;
        std::shared_ptr<Program> program;
    
    protected:
        void bindProgram();
        
        virtual void invalidateVariables();
        virtual void syncTextureSamplers();
        virtual void syncVariables();
        virtual void activateTextures();

    public:
        Material(const std::shared_ptr<Context>&);
        virtual ~Material();

        const std::shared_ptr<Context>& getContext() const;
        void setContext(const std::shared_ptr<Context>&);

        const std::shared_ptr<Program>& getProgram() const;
        void setProgram(const std::shared_ptr<Program>&);

        bool isProgramShared() const;

        virtual void bind();

        bool isVertexAttributeActive(const std::string&);
        bool isParameterActive(const std::string&);

        virtual void set(const std::string& var, float);
        virtual void set(const std::string& var, float, float);
        virtual void set(const std::string& var, float, float, float);
        virtual void set(const std::string& var, float, float, float, float);
        virtual void set(const std::string& var, unsigned size, unsigned count, const float*);

        virtual void set(const std::string& var, int);
        virtual void set(const std::string& var, int, int);
        virtual void set(const std::string& var, int, int, int);
        virtual void set(const std::string& var, int, int, int, int);
        virtual void set(const std::string& var, unsigned size, unsigned count, const int*);

        virtual void set(const std::string& var, unsigned);
        virtual void set(const std::string& var, unsigned, unsigned);
        virtual void set(const std::string& var, unsigned, unsigned, unsigned);
        virtual void set(const std::string& var, unsigned, unsigned, unsigned, unsigned);
        virtual void set(const std::string& var, unsigned size, unsigned count, const unsigned*);

        virtual void set(const std::string& var, const glm::mat2&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat3&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat4&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat2x3&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat3x2&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat2x4&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat4x2&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat3x4&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat4x3&, bool transpose = false);

        virtual void set(const std::string& var, unsigned count, const glm::mat2*, bool transpose = false);
        virtual void set(const std::string& var, unsigned count, const glm::mat3*, bool transpose = false);
        virtual void set(const std::string& var, unsigned count, const glm::mat4*, bool transpose = false);
        virtual void set(const std::string& var, unsigned count, const glm::mat2x3*, bool transpose = false);
        virtual void set(const std::string& var, unsigned count, const glm::mat3x2*, bool transpose = false);
        virtual void set(const std::string& var, unsigned count, const glm::mat2x4*, bool transpose = false);
        virtual void set(const std::string& var, unsigned count, const glm::mat4x2*, bool transpose = false);
        virtual void set(const std::string& var, unsigned count, const glm::mat3x4*, bool transpose = false);
        virtual void set(const std::string& var, unsigned count, const glm::mat4x3*, bool transpose = false);
    };
}
