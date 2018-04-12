//
//  Created by mutexre on 13/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Mesh : public virtual Object
    {
    protected:
        CoordSystem coordSystem = CoordSystem::cartesian;
        PrimitivesType primitivesType = PrimitivesType::triangles;
        std::shared_ptr<Program> program;

        struct {
            std::vector<glm::vec4> coords;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec4> colors;
            std::vector<glm::vec2> uvs;
            std::vector<unsigned> indices;
        }
        data;

        struct {
            bool enabled = false;
            unsigned indicesCount;
        }
        directMode;

        struct {
            bool indices = false;
            bool coords  = false;
            bool colors  = false;
            bool normals = false;
            bool uvs = false;
        }
        valid;

        struct {
            bool normals = true;
            bool colors = true;
            bool uvs = true;
        }
        enabled;

    public:
        Mesh();
        virtual ~Mesh();
        
        virtual void init() = 0;
        
        CoordSystem getCoordSystem() const;
        Mesh& setCoordSystem(CoordSystem);

        PrimitivesType getPrimitivesType() const;
        virtual Mesh& setPrimitivesType(PrimitivesType);

        Mesh& enableDirectMode(bool = true);

        const std::shared_ptr<Program>& getProgram() const;
        Mesh& setProgram(const std::shared_ptr<Program>&);

        const std::vector<unsigned>& getIndices() const;
        std::vector<unsigned>& getIndices();
        Mesh& setIndices(const std::vector<unsigned>&);

        const std::vector<glm::vec4>& getCoords() const;
        std::vector<glm::vec4>& getCoords();
        Mesh& setCoords(const std::vector<glm::vec4>&);

        const std::vector<glm::vec3>& getNormals() const;
        std::vector<glm::vec3>& getNormals();
        Mesh& setNormals(const std::vector<glm::vec3>&);
        
        const std::vector<glm::vec4>& getColors() const;
        std::vector<glm::vec4>& getColors();
        Mesh& setColors(const std::vector<glm::vec4>&);

        const std::vector<glm::vec2>& getUVs() const;
        std::vector<glm::vec2>& getUVs();
        Mesh& setUVs(const std::vector<glm::vec2>&);
        
        void clearIndices();
        void clearCoords();
        void clearNormals();
        void clearColors();
        void clearUVs();
        void clearAll();
        
        void invalidateIndices();
        void invalidateCoords();
        void invalidateNormals();
        void invalidateColors();
        void invalidateUVs();
        void invalidateAll();

        virtual Mesh& enableNormalsArray(bool = true);
        virtual Mesh& enableColorsArray(bool = true);
        virtual Mesh& enableUVsArray(bool = true);

        void calcNormals();

        virtual void bind() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
    };
}
