#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H

class Product {
 public:
  virtual ~Product() {}
};

class Creator {
 public:
  virtual ~Creator() {}
  virtual Product *Create() const = 0;
};

#endif  // FACTORYMETHOD_H
