//
//  Created by mutexre on 22/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Object
    {
    protected:
        std::shared_ptr<Context> context;
        std::string name;

    public:
        Object();
        Object(const std::string&);
        Object(std::string&&);
        virtual ~Object();

        const std::shared_ptr<Context>& getContext() const;
        void setContext(const std::shared_ptr<Context>&);

        const std::string& getName() const;
        void setName(const std::string&);
        void setName(std::string&&);
    };
}
