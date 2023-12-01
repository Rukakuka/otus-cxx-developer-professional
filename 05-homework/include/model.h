#include <iostream>
#include <tuple>
#include <memory>
#include <string>
#include <vector>

#include <stdlib.h>

#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include "logger.h"
#include "imodel.h"

namespace custom
{
    class Document : IDocument
    {
    public:
        Document([[maybe_unused]] std::string path,
                 [[maybe_unused]] std::shared_ptr<IDatabase *> db)
            : path(path), db(db)
        {
        }

        void Save()
        {
        }

        void Load()
        {
        }

        enum class State
        {
            IDLE,
            ADD_OBJECT,
            FILE_IO
        };

        void ChangeState([[maybe_unused]] State newState)
        {
        }

    private:
        std::string path;
        std::shared_ptr<IDatabase *> db;
    };

    /*************************************************************************/

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Point
    {
    public:
        T x;
        T y;

        Point &operator+(const Point &rhs) const
        {
        }
        Point &operator-(const Point &rhs) const
        {
        }
        Point &operator*(const T &rhs) const
        {
        }
        Point &operator/(const T &divisor) const
        {
        }
    };

    class Database : public IDatabase
    {
    public:
        int AddObject([[maybe_unused]] std::shared_ptr<IGraphicalObject *> &&object) override
        {
            return 42; // object_id
        }

        void RemoveObject([[maybe_unused]] int id) override
        {
        }

    private:
        std::vector<std::shared_ptr<IGraphicalObject *>> objects_;
    };

    /*************************************************************************/

    template <typename T>
    class BoundingBox
    {
    public:
        Point<T> anchor;
        Point<T> bound;
    };

    template <typename T>
    class GraphicalPrimitive : public IGraphicalObject
    {
    public:
        virtual void Translate() override
        {
        }
        virtual void Scale() override
        {
        }
        virtual void GetBounds() override
        {
        }

    protected:
        BoundingBox<T> boundingBox;
    };

    template <typename T>
    class Box : public GraphicalPrimitive<T>
    {
        T GetLength()
        {
        }

        T GetWidth()
        {
        }
    };

    template <typename T>
    class Circle : public GraphicalPrimitive<T>
    {
        T GetRadius()
        {
        }

        T GetCenter()
        {
        }
    };
}
