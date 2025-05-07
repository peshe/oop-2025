#ifndef INMEMORYFURNITURECATALOG_HPP
#define INMEMORYFURNITURECATALOG_HPP
#include "AbstractFurnitureCatalog.hpp"


class InMemoryFurnitureCatalog : public AbstractFurnitureCatalog {
public:
    explicit InMemoryFurnitureCatalog(std::size_t initialCapacity);

    ~InMemoryFurnitureCatalog() override;

    InMemoryFurnitureCatalog(const InMemoryFurnitureCatalog &) = delete;

    InMemoryFurnitureCatalog &operator=(const InMemoryFurnitureCatalog &) = delete;

    void create(const Furniture &furn) override;

    const Furniture &read(const char *model) const override;

    void update(const char *model, const Furniture &newFurn) override;

    void remove(const char *model) override;

private:
    void resizeData();

private:
    std::size_t capacity;
    std::size_t size;
    Furniture **data;
};


#endif //INMEMORYFURNITURECATALOG_HPP
