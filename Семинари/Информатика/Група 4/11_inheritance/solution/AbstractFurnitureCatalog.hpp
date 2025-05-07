#ifndef ABSTRACTFURNITURECATALOG_HPP
#define ABSTRACTFURNITURECATALOG_HPP

#include "Furniture.hpp"

class AbstractFurnitureCatalog {
public:
    virtual ~AbstractFurnitureCatalog() = default;

    virtual void create(const Furniture &furn) = 0;

    virtual const Furniture &read(const char *model) const = 0;

    virtual void update(const char *model, const Furniture &newFurn) = 0;

    virtual void remove(const char *model) = 0;
};

#endif //ABSTRACTFURNITURECATALOG_HPP
