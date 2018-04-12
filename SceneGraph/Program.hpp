//
//  Created by mutexre on 26/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Program : public Object
    {
        friend class Context;
        friend class Material;
        
    public:
        struct Source {
            std::string vertex, geometry, fragment;
        };

        struct Binary {
            std::vector<char> data;
        };

    protected:
        int useCount = 0;
        Source sources;
        std::shared_ptr<Binary> binary;
    
    protected:
        virtual void loadBinary() = 0;
        virtual void bind() = 0;

    public:
        virtual ~Program();
        
        int getUseCount() const;
        void adjustUseCount(int amount);
        
        const std::shared_ptr<Binary>& getBinary() const;
        
        virtual bool isVertexAttributeActive(const std::string&) = 0;
        virtual bool isUniformActive(const std::string&) = 0;
        
        virtual unsigned getVertexAttributeLocation(const std::string&) = 0;
        virtual unsigned getUniformLocation(const std::string&) = 0;

        virtual void set(const std::string& var, float);
        virtual void set(const std::string& var, float, float);
        virtual void set(const std::string& var, float, float, float);
        virtual void set(const std::string& var, float, float, float, float);
        virtual void set(const std::string& var, unsigned size, unsigned count, const float*) = 0;

        virtual void set(const std::string& var, const glm::vec2&);
        virtual void set(const std::string& var, const glm::vec3&);
        virtual void set(const std::string& var, const glm::vec4&);

        virtual void set(const std::string& var, int);
        virtual void set(const std::string& var, int, int);
        virtual void set(const std::string& var, int, int, int);
        virtual void set(const std::string& var, int, int, int, int);
        virtual void set(const std::string& var, unsigned size, unsigned count, const int*) = 0;

        virtual void set(const std::string& var, const glm::ivec2&);
        virtual void set(const std::string& var, const glm::ivec3&);
        virtual void set(const std::string& var, const glm::ivec4&);

        virtual void set(const std::string& var, unsigned);
        virtual void set(const std::string& var, unsigned, unsigned);
        virtual void set(const std::string& var, unsigned, unsigned, unsigned);
        virtual void set(const std::string& var, unsigned, unsigned, unsigned, unsigned);
        virtual void set(const std::string& var, unsigned size, unsigned count, const unsigned*) = 0;

        virtual void set(const std::string& var, const glm::uvec2&);
        virtual void set(const std::string& var, const glm::uvec3&);
        virtual void set(const std::string& var, const glm::uvec4&);

        virtual void set(const std::string& var, const glm::mat2&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat3&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat4&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat2x3&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat3x2&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat2x4&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat4x2&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat3x4&, bool transpose = false);
        virtual void set(const std::string& var, const glm::mat4x3&, bool transpose = false);

        virtual void set(const std::string& var, unsigned count, const glm::mat2*, bool transpose = false) = 0;
        virtual void set(const std::string& var, unsigned count, const glm::mat3*, bool transpose = false) = 0;
        virtual void set(const std::string& var, unsigned count, const glm::mat4*, bool transpose = false) = 0;
        virtual void set(const std::string& var, unsigned count, const glm::mat2x3*, bool transpose = false) = 0;
        virtual void set(const std::string& var, unsigned count, const glm::mat3x2*, bool transpose = false) = 0;
        virtual void set(const std::string& var, unsigned count, const glm::mat2x4*, bool transpose = false) = 0;
        virtual void set(const std::string& var, unsigned count, const glm::mat4x2*, bool transpose = false) = 0;
        virtual void set(const std::string& var, unsigned count, const glm::mat3x4*, bool transpose = false) = 0;
        virtual void set(const std::string& var, unsigned count, const glm::mat4x3*, bool transpose = false) = 0;
    };
}
