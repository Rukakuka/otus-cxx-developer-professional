#pragma once

#include <iostream>
#include <tuple>
#include <memory>
#include <string>
#include <vector>
#include <stdlib.h>

namespace custom
{

    class IGraphicalObject
    {
        virtual void Translate() = 0;
        virtual void Scale() = 0;
        virtual void GetBounds() = 0;
    };

    class IDatabase
    {
    public:
        virtual int AddObject(const std::shared_ptr<IGraphicalObject *> &object) = 0;
        virtual void RemoveObject(int id) = 0;
    };

    class IDocument
    {
        virtual void Save() = 0;
        virtual void Load(std::string path) = 0;
    };
}
