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
        shared_ptr<Program> program;

        struct {
            vector<vec4> coords;
            vector<vec3> normals;
            vector<vec4> colors;
            vector<vec2> uvs;
            vector<unsigned> indices;
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

        const shared_ptr<Program>& getProgram() const;
        Mesh& setProgram(const shared_ptr<Program>&);

        const vector<unsigned>& getIndices() const;
        vector<unsigned>& getIndices();
        Mesh& setIndices(const vector<unsigned>&);

        const vector<vec4>& getCoords() const;
        vector<vec4>& getCoords();
        Mesh& setCoords(const vector<vec4>&);

        const vector<vec3>& getNormals() const;
        vector<vec3>& getNormals();
        Mesh& setNormals(const vector<vec3>&);
        
        const vector<vec4>& getColors() const;
        vector<vec4>& getColors();
        Mesh& setColors(const vector<vec4>&);

        const vector<vec2>& getUVs() const;
        vector<vec2>& getUVs();
        Mesh& setUVs(const vector<vec2>&);
        
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
