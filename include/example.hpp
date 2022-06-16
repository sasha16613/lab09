// Copyright 2022 nikolay.sasha@mail.ru
//

#ifndef INCLUDE_EXAMPLE_HPP_
#define INCLUDE_EXAMPLE_HPP_

#include <utility>
#include <vector>

struct Power {
  float num = 60;
};

class Element {
 public:
  [[nodiscard]] virtual float CalculateResistance(const Power&) const = 0;
  virtual ~Element() = default;
};

class GroupConnections : public Element {
 protected:
  std::vector<Element*> elements;

 public:
  void addElements(Element* element) { elements.push_back(element); }
};

class SequentialConnections : public GroupConnections {
 public:
  [[nodiscard]] float CalculateResistance(const Power& p) const override {
    float sum = 0.;
    for (Element* element : elements) {
      sum += element->CalculateResistance(p);
    }
    return sum;
  }
};

class ParallelConnections : public GroupConnections {
 public:
  [[nodiscard]] float CalculateResistance(const Power& p) const override {
    float invertedSum = 0.;
    for (Element* element : elements) {
      invertedSum += 1 / element->CalculateResistance(p);
    }
    return 1 / invertedSum;
  }
};
class Combined : public Element {
 private:
  ParallelConnections pc;

 public:
  explicit Combined(ParallelConnections rhs) {
    this->pc = std::move(rhs);
  }

  [[nodiscard]] float CalculateResistance([[maybe_unused]]
                                          const Power& p) const final {
    return pc.CalculateResistance(p);
  }
};

class Resistor : public Element {
 private:
  float resistance;

 public:
  explicit Resistor(float rhs) { resistance = rhs; }

  [[nodiscard]] float CalculateResistance(
      [[maybe_unused]] const Power& p) const final {
    return resistance;
  };
};

class Capacitor : public  Element {
 private:
  float capacity;

 public:
  explicit Capacitor(float rhs) {
    capacity = rhs;
  }

  [[nodiscard]] float CalculateResistance([[maybe_unused]]
                                          const Power& p) const final {
    return 1. / (2. * 3.14 * p.num * capacity);
  }
};
class Inductor : public Element {
 private:
  float ind;

 public:
  explicit Inductor(float rhs) {
    ind = rhs;
  }

  [[nodiscard]] float CalculateResistance([[maybe_unused]] const Power& p)
      const final {
    return (p.num * ind);
  }
};

#endif  // INCLUDE_EXAMPLE_HPP_
