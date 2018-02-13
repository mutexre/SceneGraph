//
//  Created by mutexre on 22/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Object
    {
    protected:
        shared_ptr<Context> context;
        string name;

    public:
        Object();
        Object(const string&);
        Object(string&&);
        virtual ~Object();

        const shared_ptr<Context>& getContext() const;
        void setContext(const shared_ptr<Context>&);

        const string& getName() const;
        void setName(const string&);
        void setName(string&&);
    };
}
