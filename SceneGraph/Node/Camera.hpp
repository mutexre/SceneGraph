//
//  Created by mutexre on 21/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Camera : public virtual Node
    {
    public:
        enum class ProjectionType {
            orthogonal,
            perspective
        };

    private:
        ProjectionType projectionType;
        float aspect = 1.f;
        float near = 0.1f;
        float far = 1000.f;
        
        struct {
            float value, min, max;
        }
        fov = {
            0, 0, 0
        };
        
        glm::mat4 viewMatrix, projectionMatrix;
    
    public:
        static glm::mat4 getProjectionMatrix(ProjectionType, float fov, float near, float far, float aspect);

    public:
        Camera();
        Camera(const std::string& name);
        Camera(const std::string& name, ProjectionType, float fov, float near, float far, float aspect);

        ProjectionType getProjectionType() const;
        Camera& setProjectionType(ProjectionType);

        float getFov() const;
        Camera& setFov(float);

        float getMinFov() const;
        Camera& setMinFov(float);

        float getMaxFov() const;
        Camera& setMaxFov(float);

        float getNear() const;
        Camera& setNear(float);

        float getFar() const;
        Camera& setFar(float);

        float getAspectRatio() const;
        Camera& setAspectRatio(float);

        const glm::mat4& getViewMatrix() const;
        void updateViewMatrix();

        const glm::mat4& getProjectionMatrix() const;
        void updateProjectionMatrix();
        
        void update(bool recursively = true);
    };
}
